#include "Family.h"

Family::Family(int id,
                     char* latinName,
                     char* continents,
                     int speciesNumber,
                     long firstMonkeyAddress,
                     bool isRemoved) {
    this->id = id;
    this->latinName = latinName;
    this->continents = continents;
    this->speciesNumber = speciesNumber;
    this->firstMonkeyAddress = firstMonkeyAddress;
    this->isRemoved = isRemoved;
}

int Family::getId() const {
    return this->id;
}
void Family::setId(int newId) {
    this->id = newId;
}



char* Family::getLatinName() const {
    return this->latinName;
}
void Family::setLatinName(char* newLatinName) {
    this->latinName = newLatinName;
}



char* Family::getContinents() const {
    return this->continents;
}
void Family::setContinents(char* newContinents) {
    this->continents = newContinents;
}


int Family::getSpeciesNumber() const {
    return this->speciesNumber;
}
void Family::setSpeciesNumber(int newSpeciesNumber) {
    this->speciesNumber = newSpeciesNumber;
}


long Family::getFirstMonkeyAddress() const {
    return this->firstMonkeyAddress;
}
void Family::setFirstMonkeyAddress(long newAddress) {
    this->firstMonkeyAddress = newAddress;
}



bool Family::getState() const {
    return this->isRemoved;
}
void Family::setState(bool newState) {
    this->isRemoved = newState;
}



std::string Family::toString() {
    return "ID: " + std::to_string(this->id) +
           "; Latin name: " + this->latinName +
           "; Continents: " + this->continents +
           "; Species number: " + std::to_string(this->speciesNumber) +
           "; First monkey address: " + std::to_string(this->firstMonkeyAddress) +
           "; State:" + std::to_string(this->isRemoved);
}