

#ifndef DB_FUNCS_H
#define DB_FUNCS_H
#include "Utils.h"
#include "Family.h"
#include "Monkey.h"
#include "Node.h"
#include "Queue.h"
#include "Menu.h"


long getFamilyAddress(int id);

Family getFamily(int id);

void getAllFamilies();

void countFamilies();

long getMonkeyAddress(int id);

Monkey getMonkey(int id);

void getAllMonkeys();

void countMonkeys();

int countMonkeysOfFamily(int id);

bool removeFamily(int id);

bool removeMonkey(int id);

bool insertFamily(const Family& newFamily);

bool insertMonkey(Monkey& newMonkey);

bool updateFamily(int id, const Family& newFamily);

bool updateMonkey(int id, const Monkey& newMonkey);

bool checkFamilyId(int id);

bool checkMonkeyId(int id);

void loadIndex(char* filePath, ListNode** head);

void loadGarbage(char* filePath, Queue** garbage);

void prepareFiles(char* familiesPath,
                  char* monkeysPath,
                  char* familiesIndexPath,
                  char* monkeysIndexPath,
                  char* familiesGarbagePath,
                  char* monkeysGarbagePath);

void close(char* familiesIndexPath, char* monkeysIndexPath, char* familiesGarbagePath, char* monkeysGarbagePath);

#endif //DB_FUNCS_H
