#include "Monkey.h"

Monkey::Monkey(int id,
               int familyId,
               char* latinName,
               int avgSize,
               int avgLifespan,
               char* securityStatus,
               int approxPopulation,
               char* hierarchy,
               long prevMonkeyAddress,
               long nextMonkeyAddress,
               bool isRemoved) {
    this->id = id;
    this->familyId = familyId;
    this->setLatinName(latinName);
    this->avgSize = avgSize;
    this->avgLifespan = avgLifespan;
    this->securityStatus = securityStatus;
    this->approxPopulation = approxPopulation;
    this->hierarchy = hierarchy;
    this->prevMonkeyAddress = prevMonkeyAddress;
    this->nextMonkeyAddress = nextMonkeyAddress;
    this->isRemoved = isRemoved;
}
int Monkey::getId() const {
    return this->id;
}
void Monkey::setId(int newId) {
    this->id = newId;
}


int Monkey::getFamilyId() const {
    return this->familyId;
}
void Monkey::setFamilyId(int newFamilyId) {
    this->familyId = newFamilyId;
}


char* Monkey::getLatinName() const {
    return this->latinName;
}
void Monkey::setLatinName(char* newLatinName) {
    this->latinName = newLatinName;
}


int Monkey::getAvgSize() const {
    return this->avgSize;
}
void Monkey::setAvgSize(int newAvgSize) {
    this->avgSize = newAvgSize;
}

int Monkey::getAvgLifespan() const {
    return this->avgSize;
}
void Monkey::setAvgLifespan(int newAvgLifespan) {
    this->avgLifespan = newAvgLifespan;
}


char* Monkey::getSecurityStatus() const {
    return this->securityStatus;
}
void Monkey::setSecurityStatus(char* newSecurityStatus) {
    this->securityStatus = newSecurityStatus;
}


int Monkey::getApproxPopulation() const {
    return this->approxPopulation;
}
void Monkey::setApproxPopulation(int newApproxPopulation) {
    this->approxPopulation = newApproxPopulation;
}


char* Monkey::getHierarchy() const {
    return this->hierarchy;
}
void Monkey::setHierarchy(char* newHierarchy) {
    this->hierarchy = newHierarchy;
}

long Monkey::getPrevMonkeyAddress() const {
    return this->prevMonkeyAddress;
}
void Monkey::setPrevMonkeyAddress(long newAddress) {
    this->prevMonkeyAddress = newAddress;
}


long Monkey::getNextMonkeyAddress() const {
    return this->nextMonkeyAddress;
}
void Monkey::setNextMonkeyAddress(long newAddress) {
    this->nextMonkeyAddress = newAddress;
}


bool Monkey::getState() const {
    return this->isRemoved;
}
void Monkey::setState(bool newState) {
    this->isRemoved = newState;
}

std::string Monkey::toString() const {
    return "ID: " + std::to_string(this->id) +
           "; Family ID: " + std::to_string(this->familyId) +
           "; Latin Name: " + this->latinName +
           "; Average size: " + std::to_string(this->avgSize) +
           "; Average lifespan: " + std::to_string(this->avgLifespan) +
           "; Security status: " + this->securityStatus +
           "; Approximate population: " + std::to_string(this->approxPopulation) +
           "; Hierarchy: " + this->hierarchy +
           "; Previous monkey address " + std::to_string(this->prevMonkeyAddress) +
           "; Next monkey address " + std::to_string(this->nextMonkeyAddress) +
           "; State: " + std::to_string(this->isRemoved) + '\n';
}