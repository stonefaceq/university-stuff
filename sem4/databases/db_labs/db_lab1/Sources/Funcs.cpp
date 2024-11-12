#include "Funcs.h"
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
#include <functional>

FILE* familiesF;
FILE* monkeysF;

ListNode* familiesIndex = new ListNode;
Queue* familiesGarbage = new Queue;

ListNode* monkeysIndex = new ListNode;
Queue* monkeysGarbage = new Queue;

long getFamilyAddress(int id) {
    long address;
    processFamily([&]() {
        address = getAddress(id, familiesIndex);
    });
    return address;
}

Family getFamily(int id) {
    long address = getFamilyAddress(id);
    if (address == -1) {
        //std::cerr << "No family with such ID\n";
        return Family();
    }
    return readFamily(familiesF, address);
}

void getAllFamilies() {
    if (familiesIndex->id == -1) {
        std::cout << "No families.\n";
        return;
    }

    ListNode* temp = familiesIndex;
    while (temp) {
        int id = temp->id;
        Family family = getFamily(id);
        std::cout << family.toString() << '\n';
        temp = temp->next;
    }
}

void countFamilies() {
    std::cout << "Total families: " << getSize(familiesIndex) << '\n';
}

long getMonkeyAddress(int id) {
    return getAddress(id, monkeysIndex);
}

Monkey getMonkey(int id) {
    long address = getMonkeyAddress(id);
    if (address == -1) {
        std::cerr << "No monkey with such ID.\n";
        return Monkey();
    }
    return readMonkey(monkeysF, address);
}

void getAllMonkeys() {
    if (monkeysIndex->id == -1) {
        std::cout << "No monkeys.\n";
        return;
    }

    ListNode* temp = monkeysIndex;
    while (temp) {
        int id = temp->id;
        Monkey monkey = getMonkey(id);
        std::cout << monkey.toString() << '\n';
        temp = temp->next;
    }
}

void countMonkeys() {
    std::cout << "Total monkeys: " << getSize(monkeysIndex) << '\n';
}

int countMonkeysOfFamily(int id) {
    Family family = getFamily(id);
    long address = family.getFirstMonkeyAddress();

    int count = 0;
    while (address != -1) {
        Monkey monkey = readMonkey(monkeysF, address);
        ++count;
        address = monkey.getNextMonkeyAddress();
    }
    return count;
}

bool removeFamily(int id) {
   Family family = getFamily(id);
    if (family.getId() == -1) {
        return false;
    }
    family.setState(STATE_REMOVED);

    long address = getFamilyAddress(id);
    writeFamily(familiesF, family, address);

    familiesGarbage->push(address);
    deleteListNode(id, &familiesIndex);

    // deleting all sub records
    long monkeyAddress = family.getFirstMonkeyAddress();

    while (monkeyAddress != -1) {
        Monkey monkey = readMonkey(monkeysF, monkeyAddress);
        monkey.setState(STATE_REMOVED);
        writeMonkey(monkeysF, monkey, monkeyAddress);
        monkeysGarbage->push(monkeyAddress);
        deleteListNode(monkey.getId(), &monkeysIndex);
        monkeyAddress = monkey.getNextMonkeyAddress();
    }
    return true;
}

bool removeMonkey(int id) {
    Monkey monkey = getMonkey(id);
    if (monkey.getId() == -1) {
        return false;
    }
    monkey.setState(STATE_REMOVED);

    long prevMonkeyAddress = monkey.getPrevMonkeyAddress();
    long nextMonkeyAddress = monkey.getNextMonkeyAddress();

    if (prevMonkeyAddress != -1) {
        // changing relations between monkeys
        Monkey prevMonkey = readMonkey(monkeysF, prevMonkeyAddress);
        prevMonkey.setNextMonkeyAddress(nextMonkeyAddress);
        writeMonkey(monkeysF, prevMonkey, prevMonkeyAddress);

        if (nextMonkeyAddress != -1) {
            Monkey nextMonkey = readMonkey(monkeysF, nextMonkeyAddress);
            nextMonkey.setPrevMonkeyAddress(prevMonkeyAddress);
            writeMonkey(monkeysF, nextMonkey, nextMonkeyAddress);
        }
    }
    else {
        // setting family first monkey to the next one
        int familyId = monkey.getFamilyId();
        Family family = getFamily(familyId);
        family.setFirstMonkeyAddress(nextMonkeyAddress);
        updateFamily(familyId, family);
    }

    long address = getMonkeyAddress(id);
    if (address == -1) {
        return false;
    }

    writeMonkey(monkeysF, monkey, address);
    monkeysGarbage->push(address);
    deleteListNode(id, &monkeysIndex);
    return true;
}

bool insertFamily(const Family& newFamily) {
    long address = familiesGarbage->pop();
    if (address == -1) {
        fseek(familiesF, 0, SEEK_END);
        address = ftell(familiesF);
    }
    int id = newFamily.getId();
    addListNode(id, address, &familiesIndex);
    sortList(&familiesIndex);

    writeFamily(familiesF, newFamily, address);
    return true;
}

bool insertMonkey(Monkey& newMonkey) {
    int familyId = newMonkey.getFamilyId();

    long address = monkeysGarbage->pop();
    if (address == -1) {
        fseek(monkeysF, 0, SEEK_END);
        address = ftell(monkeysF);
    }

    Family family = getFamily(familyId);
    long monkeyAddress = family.getFirstMonkeyAddress();

    if (monkeyAddress == -1) {
        family.setFirstMonkeyAddress(address);

        long familyAddress = getFamilyAddress(familyId);
        writeFamily(familiesF, family, familyAddress);
    }
    else {
        Monkey monkey = readMonkey(monkeysF, monkeyAddress);
        while (monkey.getNextMonkeyAddress() != -1) {
            monkeyAddress = monkey.getNextMonkeyAddress();
            monkey = readMonkey(monkeysF, monkeyAddress);
        }
        monkey.setNextMonkeyAddress(address);
        newMonkey.setPrevMonkeyAddress(monkeyAddress);

        writeMonkey(monkeysF, monkey, monkeyAddress);
    }

    addListNode(newMonkey.getId(), address, &monkeysIndex);
    sortList(&monkeysIndex);

    writeMonkey(monkeysF, newMonkey, address);
    return true;
}

bool updateFamily(int id, const Family& newFamily) {
    long address = getFamilyAddress(id);
    if (address == -1) {
        //std::cerr << "No family with such ID\n";
        return false;
    }
    writeFamily(familiesF, newFamily, address);
    return true;
}

bool updateMonkey(int id, const Monkey& newMonkey) {
    long address = getMonkeyAddress(id);
    if (address == 1) {
        std::cerr << "No monkey with such ID\n";
        return false;
    }
    writeMonkey(monkeysF, newMonkey, address);
    return true;
}

bool checkFamilyId(int id) {
    return isIdFree(id, familiesIndex);
}

bool checkMonkeyId(int id) {
    return isIdFree(id, monkeysIndex);
}

void loadIndex(char* filePath, ListNode** head) {
    FILE* file = fopen(filePath, "rb+");
    if (!file) {
        file = fopen(filePath, "wb+");
    }

    if (!isFileEmpty(file)) {
        int id;
        long address;

        do {
            fread(&id, INT_SIZE, 1, file);
            fread(&address, LONG_SIZE, 1, file);
            addListNode(id, address, head);
        } while (!feof(file));
    }
    sortList(head);
    fclose(file);
}

void writeIndex(char* filePath, ListNode* head) {
    FILE* file = fopen(filePath, "wb+");

    ListNode* temp = head;
    if (temp->id == -1) {
        return;
    }

    while(temp) {
        fwrite(&temp->id, INT_SIZE, 1, file);
        fwrite(&temp->address, LONG_SIZE, 1, file);
        temp = temp->next;
    }
    fclose(file);
}

void loadGarbage(char* filePath, Queue** garbage) {
    FILE* file = fopen(filePath, "rb+");
    if (!file) {
        file = fopen(filePath, "wb+");
    }

    if (!isFileEmpty(file)) {
        long address;
        do {
            fread(&address, LONG_SIZE, 1, file);
            (*garbage)->push(address);
        } while (!feof(file));
    }
    fclose(file);
}

void writeGarbage(char* filePath, Queue* garbage) {
    FILE* file = fopen(filePath, "wb+");

    while(!garbage->isEmpty()) {
        long address = garbage->pop();
        fwrite(&address, LONG_SIZE, 1, file);
    }
    fclose(file);
}

void prepareFiles(char* familiesPath, char* monkeysPath, char* familiesIndexPath, char* monkeysIndexPath, char* familiesGarbagePath, char* monkeysGarbagePath) {
    familiesF = fopen(familiesPath, "rb+");
    if (!familiesF) {
        familiesF = fopen(familiesPath, "wb+");
    }

    monkeysF = fopen(monkeysPath, "rb+");
    if (!monkeysF) {
        monkeysF = fopen(monkeysPath, "wb+");
    }

    loadIndex(familiesIndexPath, &familiesIndex);
    loadIndex(monkeysIndexPath, &monkeysIndex);

    loadGarbage(familiesGarbagePath, &familiesGarbage);
    loadGarbage(monkeysGarbagePath, &monkeysGarbage);
}

void close(char* familiesIndexPath, char* monkeysIndexPath, char* familiesGarbagePath, char* monkeysGarbagePath) {
    fclose(familiesF);
    writeIndex(familiesIndexPath, familiesIndex);
    writeGarbage(familiesGarbagePath, familiesGarbage);

    fclose(monkeysF);
    writeIndex(monkeysIndexPath, monkeysIndex);
    writeGarbage(monkeysGarbagePath, monkeysGarbage);
}