
#ifndef DB_MENU_H
#define DB_MENU_H

#include <iostream>
#include "Const.h"
#include "Family.h"
#include "Monkey.h"
#include "Funcs.h"

int readInt(const char* text);

char* readString(const char* text);

void addFamilyMenu();
void getFamilyMenu();
void removeFamilyMenu();
void updateFamilyMenu();

void updateFamilyLatinName(Family& family);
void updateFamilyContinents(Family& family);
void updateFamilyFields(Family& family);



void addMonkeyMenu();
void getMonkeyMenu();
void removeMonkeyMenu();
void updateMonkeyMenu();

void updateMonkeyLatinName(Monkey& monkey);
void updateMonkeySecurityStatus(Monkey& monkey);
void updateMonkeyHierarchy(Monkey& monkey);
void updateMonkeyFields(Monkey& monkey);


void countMonkeysOfFamilyMenu();

void start();

#endif //DB_MENU_H
