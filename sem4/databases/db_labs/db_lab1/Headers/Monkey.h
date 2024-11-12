#ifndef DB_MONKEY_H
#define DB_MONKEY_H

#include <iostream>
#include <string>
#include "Const.h"

struct Monkey
{
public:
    Monkey(int id,
         int familyId,
         char* latinName,
         int avgSize,
         int avgLifespan,
         char* securityStatus,
         int approxPopulation,
         char* hierarchy,
         long prevMonkeyAddress,
         long nextMonkeyAddress,
         bool state = STATE_ACTIVE);

    Monkey() = default;

    int getId() const;
    void setId(int newId);

    int getFamilyId() const;
    void setFamilyId(int newFamilyId);

    char* getLatinName() const;
    void setLatinName(char* newLatinName);

    int getAvgSize() const;
    void setAvgSize(int newAvgSize);

    int getAvgLifespan() const;
    void setAvgLifespan(int newAvgLifespan);

    char* getSecurityStatus() const;
    void setSecurityStatus(char* newSecurityStatus);

    int getApproxPopulation() const;
    void setApproxPopulation(int newApproxPopulation);

    char* getHierarchy() const;
    void setHierarchy(char* newHierarchy);

    long getPrevMonkeyAddress() const;
    void setPrevMonkeyAddress(long newAddress);


    long getNextMonkeyAddress() const;
    void setNextMonkeyAddress(long newAddress);

    bool getState() const;
    void setState(bool newState);

    std::string toString() const;

private:
    int id = -1;
    int familyId = -1;
    char* latinName = new char[STRING_SIZE];
    int avgSize = -1;
    int avgLifespan = -1;
    char* securityStatus = new char[STRING_SIZE];
    int approxPopulation = -1;
    char* hierarchy = new char[STRING_SIZE];
    long prevMonkeyAddress = -1;
    long nextMonkeyAddress = -1;
    bool isRemoved = STATE_ACTIVE;
};

#endif //DB_MONKEY_H
