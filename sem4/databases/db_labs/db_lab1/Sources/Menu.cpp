#include "Menu.h"

const char* MAIN_MENU_OPTIONS_TEXT = "----------------------------------------\n"
                                     "| [0] – Exit                     |\n| [1]"
                                     " – Insert family            |\n| [2] – Get family               |\n| [3]"
                                     " – Delete family            |\n| [4] – Update family            |\n| [5]"
                                     " – Insert monkey            |\n| [6] – Get monkey               |\n| [7]"
                                     " – Delete monkey            |\n| [8] – Update monkey            |\n| [9]"
                                     " – Count families           |\n| [10] – Count monkeys           |\n| [11]"
                                     " – Count monkeys in family |\n| [12] - Get all families          |\n| [13]"
                                     " - Get all monkeys           |\n"
                                     "----------------------------------------\n";

const char* MAIN_MENU_WRONG_INPUT = "Enter value between 0 and 4\n";

const char* FAMILY_ID_REQUEST_TEXT = "Enter familyID (only positive integers).\n";
const char* FAMILY_NAME_REQUEST_TEXT = "Enter family name (in latin).\n";
const char* FAMILY_CONTINENTS_REQUEST_TEXT = "Enter family continents.\n";
const char* FAMILY_NUMBER_OF_SPECIES_REQUEST_TEXT = "Enter a number of species in family.\n";

const char* FAMILY_INSERTED_TEXT = "Family has been successfully inserted.\n";
const char* FAMILY_REMOVED_TEXT = "Family has been successfully removed.\n";

const char* FAMILY_SELECT_FIELD_TO_UPDATE = "0 - Stop updating\n1 - Name\n2 - Continents\n 3 - Species number\n";
const char* FAMILY_UPDATED_TEXT = "Family has been successfully updated.\n";

const char* FAMILY_INVALID_ID_TEXT = "No family with such ID.\n";
const char* FAMILY_ID_IS_TAKEN_TEXT = "This ID is already taken.\n";
const char* FAMILY_NOT_REMOVED_TEXT = "Error while removing the family.\n";
const char* FAMILY_NOT_UPDATED_TEXT = "Error while updating the family.\n";

const char* MONKEY_ID_REQUEST_TEXT = "Enter monkey ID.\n";
const char* MONKEY_FAMILY_ID_REQUEST_TEXT = "Enter monkey's family ID.\n";
const char* MONKEY_AVG_SIZE_REQUEST_TEXT = "Enter monkey average size.\n";
const char* MONKEY_NAME_REQUEST_TEXT = "Enter monkey name in latin.\n";
const char* MONKEY_AVG_LIFESPAN_REQUEST_TEXT = "Enter monkey average lifespan.\n";
const char* MONKEY_APPROX_POPULATION_REQUEST_TEXT = "Enter monkey approximate population.\n";
const char* MONKEY_SECURITY_STATUS_REQUEST_TEXT = "Enter monkey security status.\n";
const char* MONKEY_HIERARCHY_REQUEST_TEXT = "Enter monkey hierarchy.\n";


const char* MONKEY_INVALID_ID_TEXT = "No monkey with such ID\n";
const char* MONKEY_ID_IS_TAKEN_TEXT = "This ID is already taken.\n";
const char* MONKEY_NOT_REMOVED_TEXT = "Error while removing the monkey.\n";
const char* MONKEY_NOT_UPDATED_TEXT = "Error while updating the monkey\n";

const char* MONKEY_INSERTED_TEXT = "Monkey has been successfully inserted.\n";
const char* MONKEY_REMOVED_TEXT = "Monkey has been successfully removed.\n";

const char* MONKEY_SELECT_FIELDS_TO_UPDATE_TEXT = "0 - Stop updating\n1 - Name\n2 - Avg. Size\n3 - Avg. Lifespan\n 4 - Security status\n 5 - Approx. Population\n 6 - Hierarchy\n";
const char* MONKEY_UPDATED_TEXT = "Monkey has been successfully updated.\n";

const char* FAMILY_COUNT_RESULT_TEXT = "Families count: ";
const char* MONKEY_COUNT_RESULT_TEXT = "Monkeys count: ";
const char* FAMILIES_MONKEYS_COUNT_RESULT_TEXT = "Family's monkeys count: ";

int readInt(const char* text)
{
    int value;
    std::cout << text;
    std::cin >> value;
    return value;
}

char* readString(const char* text)
{
    char* string = new char[STRING_SIZE];
    std::cout << text;
    std::cin >> string;
    return string;
}

void addFamilyMenu()
{
    int id;
    while (true)
    {
        id = readInt(FAMILY_ID_REQUEST_TEXT);

        if (!checkFamilyId(id))
        {
            std::cout << FAMILY_ID_IS_TAKEN_TEXT;
            continue;
        }

        break;
    }

    char* name = readString(FAMILY_NAME_REQUEST_TEXT);
    char* continents = readString(FAMILY_CONTINENTS_REQUEST_TEXT);
    int speciesNumber = readInt(FAMILY_NUMBER_OF_SPECIES_REQUEST_TEXT);

    Family family(id, name, continents, speciesNumber, -1);
    insertFamily(family);

    std::cout << FAMILY_INSERTED_TEXT;
}

void getFamilyMenu()
{
    int id = readInt(FAMILY_ID_REQUEST_TEXT);

    Family family = getFamily(id);
    if (family.getId() == -1) {
        std::cout << FAMILY_INVALID_ID_TEXT;
        return;
    }

    std::cout << family.toString();
}

void removeFamilyMenu()
{
    int id = readInt(FAMILY_ID_REQUEST_TEXT);
    bool success = removeFamily(id);
    if (!success)
    {
        std::cout << FAMILY_NOT_REMOVED_TEXT;
        return;
    }
    std::cout << FAMILY_REMOVED_TEXT;
}

void updateFamilyName(Family& family)
{
    char* name = readString(FAMILY_NAME_REQUEST_TEXT);
    family.setLatinName(name);
}

void updateFamilyContinents(Family& family)
{
    char* continents = readString(FAMILY_CONTINENTS_REQUEST_TEXT);
    family.setContinents(continents);
}

void updateFamilyNumberOfSpecies(Family& family)
{
    int speciesNumber = readInt(FAMILY_NUMBER_OF_SPECIES_REQUEST_TEXT);
    family.setSpeciesNumber(speciesNumber);
}

void updateFamilyFields(Family& family)
{
    int option;
    do
    {
        option = readInt(FAMILY_SELECT_FIELD_TO_UPDATE);
        switch (option)
        {
            case 0:
                break;
            case 1:
                updateFamilyName(family);
                break;
            case 2:
                updateFamilyContinents(family);
                break;
            case 3:
                updateFamilyNumberOfSpecies(family);
                break;
            default:
                break;
        }
    } while (option != 0);
}

void updateFamilyMenu()
{
    int id = readInt(FAMILY_ID_REQUEST_TEXT);
    Family family = getFamily(id);

    if (family.getId() == -1) {
        std::cout << FAMILY_INVALID_ID_TEXT;
        return;
    }

    updateFamilyFields(family);

    bool success = updateFamily(id, family);
    if (!success)
    {
        std::cout << FAMILY_NOT_UPDATED_TEXT;
        return;
    }

    std::cout << FAMILY_UPDATED_TEXT;
}

void addMonkeyMenu()
{
    int id;
    while (true)
    {
        id = readInt(MONKEY_ID_REQUEST_TEXT);
        if (!checkMonkeyId(id))
        {
            std::cout << MONKEY_ID_IS_TAKEN_TEXT;
            continue;
        }
        break;
    }

    int familyId = readInt(MONKEY_FAMILY_ID_REQUEST_TEXT);
    Family family = getFamily(familyId);
    if (family.getId() == -1) {
        std::cout << FAMILY_INVALID_ID_TEXT;
        return;
    }


    char* name = readString(MONKEY_NAME_REQUEST_TEXT);
    int avgSize = readInt(MONKEY_AVG_SIZE_REQUEST_TEXT);
    int avgLifespan = readInt(MONKEY_AVG_LIFESPAN_REQUEST_TEXT);
    char* securityStatus = readString(MONKEY_SECURITY_STATUS_REQUEST_TEXT);
    int approxPopulation = readInt(MONKEY_APPROX_POPULATION_REQUEST_TEXT);
    char* hierarchy = readString(MONKEY_HIERARCHY_REQUEST_TEXT);

    Monkey monkey(id, familyId, name, avgSize, avgLifespan, securityStatus, approxPopulation, hierarchy, -1, -1);
    insertMonkey(monkey);

    std::cout << MONKEY_INSERTED_TEXT;
}

void getMonkeyMenu()
{
    int id = readInt(MONKEY_ID_REQUEST_TEXT);

    Monkey monkey = getMonkey(id);
    if (monkey.getId() == -1)
    {
        std::cout << MONKEY_INVALID_ID_TEXT;
        return;
    }

    std::cout << monkey.toString();
}

void removeMonkeyMenu()
{
    int id = readInt(MONKEY_ID_REQUEST_TEXT);
    bool success = removeMonkey(id);
    if (!success)
    {
        std::cout << MONKEY_NOT_REMOVED_TEXT;
        return;
    }
    std::cout  << MONKEY_REMOVED_TEXT;
}

void updateMonkeyLatinName(Monkey& monkey)
{
    char* name = readString(MONKEY_NAME_REQUEST_TEXT);
    monkey.setLatinName(name);
}

void updateMonkeySize(Monkey& monkey)
{
    int size = readInt(MONKEY_AVG_SIZE_REQUEST_TEXT);
    monkey.setAvgSize(size);
}

void updateMonkeyLifespan(Monkey& monkey)
{
    int lifespan = readInt(MONKEY_AVG_LIFESPAN_REQUEST_TEXT);
    monkey.setAvgSize(lifespan);
}

void updateMonkeySecurityStatus(Monkey& monkey) {
    char* secStatus = readString(MONKEY_SECURITY_STATUS_REQUEST_TEXT);
    monkey.setSecurityStatus(secStatus);
}

void updateMonkeyApproxPopulation(Monkey& monkey) {
    int approxPopulation = readInt(MONKEY_APPROX_POPULATION_REQUEST_TEXT);
    monkey.setApproxPopulation(approxPopulation);
}

void updateMonkeyHierarchy(Monkey& monkey) {
    char* hierarchy = readString(MONKEY_HIERARCHY_REQUEST_TEXT);
    monkey.setHierarchy(hierarchy);
}

void updateMonkeyFields(Monkey& monkey)
{
    int options;
    do
    {
        options = readInt(MONKEY_SELECT_FIELDS_TO_UPDATE_TEXT);
        switch (options)
        {
            case 1:
                updateMonkeyLatinName(monkey);
                break;
            case 2:
                updateMonkeySize(monkey);
                break;
            case 3:
                updateMonkeyLifespan(monkey);
                break;
            case 4:
                updateMonkeySecurityStatus(monkey);
                break;
            case 5:
                updateMonkeyApproxPopulation(monkey);
                break;
            case 6:
                updateMonkeyHierarchy(monkey);
                break;
            default:
                break;
        }
    } while (options != 0);
}

void updateMonkeyMenu()
{
    int id = readInt(MONKEY_ID_REQUEST_TEXT);

    Monkey monkey = getMonkey(id);
    if (monkey.getId() == -1)
    {
        std::cout << MONKEY_INVALID_ID_TEXT;
        return;
    }

    updateMonkeyFields(monkey);
    updateMonkey(id, monkey);
}

void countMonkeysOfFamilyMenu() {
    int id = readInt(FAMILY_ID_REQUEST_TEXT);

    Family family = getFamily(id);
    if (family.getId() == -1) {
        std::cout << FAMILY_INVALID_ID_TEXT;
        return;
    }

    std::cout << "Total monkeys of this family: " << countMonkeysOfFamily(id);
}



void start()
{
    int option;
    do
    {
        std::cout << "\n\n";
        option = readInt(MAIN_MENU_OPTIONS_TEXT);
        switch (option)
        {
            case 0:
                break;
            case 1:
                addFamilyMenu();
                break;
            case 2:
                getFamilyMenu();
                break;
            case 3:
                removeFamilyMenu();
                break;
            case 4:
                updateFamilyMenu();
                break;
            case 5:
                addMonkeyMenu();
                break;
            case 6:
                getMonkeyMenu();
                break;
            case 7:
                removeMonkeyMenu();
                break;
            case 8:
                updateMonkeyMenu();
                break;
            case 9:
                countFamilies();
                break;
            case 10:
                countMonkeys();
                break;
            case 11:
                countMonkeysOfFamilyMenu();
                break;
            case 12:
                getAllFamilies();
                break;
            case 13:
                getAllMonkeys();
                break;
            default:
                std::cout << MAIN_MENU_WRONG_INPUT;
                break;
        }
    } while (option != 0);
}