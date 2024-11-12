#include "Utils.h"

void writeMonkey(FILE* file, const Monkey& monkey) {
    int id = monkey.getId();
    int familyId = monkey.getFamilyId();
    char* latinName = monkey.getLatinName();
    int avgSize = monkey.getAvgSize();
    int avgLifespan = monkey.getAvgLifespan();
    char* securityStatus = monkey.getSecurityStatus();
    int approxPopulation = monkey.getApproxPopulation();
    char* hierarchy = monkey.getHierarchy();
    long prevMonkeyAddress = monkey.getPrevMonkeyAddress();
    long nextMonkeyAddress = monkey.getNextMonkeyAddress();
    bool state = monkey.getState();

    fwrite(&id, INT_SIZE, 1, file);
    fwrite(&familyId, INT_SIZE, 1, file);
    fwrite(latinName, CHAR_SIZE, STRING_SIZE, file);
    fwrite(&avgSize, INT_SIZE, 1, file);
    fwrite(&avgLifespan, INT_SIZE, 1, file);
    fwrite(securityStatus, CHAR_SIZE, STRING_SIZE, file);
    fwrite(&approxPopulation, INT_SIZE, 1, file);
    fwrite(hierarchy, CHAR_SIZE, STRING_SIZE, file);
    fwrite(&prevMonkeyAddress, LONG_SIZE, 1, file);
    fwrite(&nextMonkeyAddress, LONG_SIZE, 1, file);
    fwrite(&state, BOOL_SIZE, 1, file);
}

void writeMonkey(FILE* file, const Monkey& monkey, long address) {
    fseek(file, address, SEEK_SET);
    writeMonkey(file, monkey);
}

Monkey readMonkey(FILE* file) {
    int id;
    int familyId;
    char* latinName = new char[STRING_SIZE];
    int avgSize;
    int avgLifespan;
    char* securityStatus = new char[STRING_SIZE];
    int approxPopulation;
    char* hierarchy = new char[STRING_SIZE];
    long prevMonkeyAddress;
    long nextMonkeyAddress;
    bool state;


    fread(&id, INT_SIZE, 1, file);
    fread(&familyId, INT_SIZE, 1, file);
    fread(latinName, CHAR_SIZE, STRING_SIZE, file);
    fread(&avgSize, INT_SIZE, 1, file);
    fread(&avgLifespan, INT_SIZE, 1, file);
    fread(securityStatus, CHAR_SIZE, STRING_SIZE, file);
    fread(&approxPopulation, INT_SIZE, 1, file);
    fread(hierarchy, CHAR_SIZE, STRING_SIZE, file);
    fread(&prevMonkeyAddress, LONG_SIZE, 1, file);
    fread(&nextMonkeyAddress, LONG_SIZE, 1, file);
    fread(&state, BOOL_SIZE, 1, file);

    return {id, familyId, latinName, avgSize, avgLifespan, securityStatus, approxPopulation, hierarchy, prevMonkeyAddress, nextMonkeyAddress};
}

Monkey readMonkey(FILE* file, long address) {
    fseek(file, address, SEEK_SET);
    return readMonkey(file);
}

void writeFamily(FILE* file, const Family& family) {
    int id = family.getId();
    char* latinName = family.getLatinName();
    char* continents = family.getContinents();
    int speciesNumber = family.getSpeciesNumber();
    long firstMonkeyAddress = family.getFirstMonkeyAddress();
    bool state = family.getState();

    fwrite(&id, INT_SIZE, 1, file);
    fwrite(latinName, CHAR_SIZE, STRING_SIZE, file);
    fwrite(continents, CHAR_SIZE, STRING_SIZE, file);
    fwrite(&speciesNumber, INT_SIZE, 1, file);
    fwrite(&firstMonkeyAddress, LONG_SIZE, 1, file);
    fwrite(&state, BOOL_SIZE, 1, file);

}

void writeFamily(FILE* file, Family family, long address) {
    fseek(file, address, SEEK_SET);
    writeFamily(file, family);
}

Family readFamily(FILE* file) {
    int id;
    char* latinName = new char[STRING_SIZE];
    char* continents = new char[STRING_SIZE];
    int speciesNumber;
    long firstMonkeyAddress;
    bool state;

    fread(&id, INT_SIZE, 1, file);
    fread(latinName, CHAR_SIZE, STRING_SIZE, file);
    fread(continents, CHAR_SIZE, STRING_SIZE, file);
    fread(&speciesNumber, INT_SIZE, 1, file);
    fread(&firstMonkeyAddress, LONG_SIZE, 1, file);
    fread(&state, BOOL_SIZE, 1, file);

    return {id, latinName, continents, speciesNumber, firstMonkeyAddress};
}

Family readFamily(FILE* file, long address) {
    fseek(file, address, SEEK_SET);
    return readFamily(file);
}

bool isFileEmpty(FILE* file) {
    fseek(file, 0, SEEK_END);
    long address = ftell(file);
    fseek(file, 0, SEEK_SET);
    return address == 0;
}