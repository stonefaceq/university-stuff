
#ifndef DB_UTILS_H
#define DB_UTILS_H

#include "Monkey.h"
#include "Family.h"

void writeMonkey(FILE* file, const Monkey& monkey);

void writeMonkey(FILE* file, const Monkey& monkey, long address);

Monkey readMonkey(FILE* file);

Monkey readMonkey(FILE* file, long address);

void writeFamily(FILE* file, const Family& family);

void writeFamily(FILE* file, Family family, long address);

Family readFamily(FILE* file);

Family readFamily(FILE* file, long address);

bool isFileEmpty(FILE* file);

#endif //DB_UTILS_H
