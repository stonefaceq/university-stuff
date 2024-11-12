
#include <iostream>
#include "Menu.h"
#include "Funcs.h"

int main() {
    prepareFiles("Families.bin",
                 "Monkeys.bin",
                 "FamiliesIndex.bin",
                 "MonkeysIndex.bin",
                 "FamiliesGarbage.bin",
                 "monkeysGarbage.bin");
    start();
    close("FamiliesIndex.bin",
          "MonkeysIndex.bin",
          "FamiliesGarbage.bin",
          "monkeysGarbage.bin");
    return 0;
}