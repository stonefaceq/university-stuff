
#ifndef DB_FAMILY_H
#define DB_FAMILY_H
#include <string>
#include "Const.h"


struct Family
{
public:
    Family(int id,
           char* latinName,
           char* continents,
           int speciesNumber,
           long firstMonkeyAddress,
           bool state = STATE_ACTIVE);

    Family() = default;

    int getId() const;
    void setId(int newID);

    char* getLatinName() const;
    void setLatinName(char* newLatinName);

    char* getContinents() const;
    void setContinents(char* newContinents);

    int getSpeciesNumber() const;
    void setSpeciesNumber(int newSpeciesNumber);

    long getFirstMonkeyAddress() const;
    void setFirstMonkeyAddress(long newAddress);

    bool getState() const;
    void setState(bool newState);

    std::string toString();
private:
    int id = -1;
    char* latinName = new char[STRING_SIZE];
    char* continents = new char[STRING_SIZE];
    int speciesNumber = -1;
    long firstMonkeyAddress = -1;
    bool isRemoved = STATE_ACTIVE;
};
#endif //DB_FAMILY_H
