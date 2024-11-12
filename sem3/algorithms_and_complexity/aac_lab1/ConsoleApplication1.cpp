#include <iostream>
#include <string>
#include <vector>

// Реалізація алгоритму Кнута-Морріса-Пратта
std::vector<int> computeLPSArray(const std::string& pattern) {
    int len = 0;
    std::vector<int> lps(pattern.length(), 0);

    int i = 1;
    while (i < pattern.length()) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else {
            if (len != 0) {
                len = lps[len - 1];
            }
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

bool isCyclicRotation(const std::string& T, const std::string& TStar) {
    if (T.length() != TStar.length()) {
        return false;
    }

    std::string combinedString = T + T;
    std::vector<int> lps = computeLPSArray(TStar);

    int i = 0; // Індекс для combinedString
    int j = 0; // Індекс для TStar

    while (i < combinedString.length()) {
        if (TStar[j] == combinedString[i]) {
            i++;
            j++;
            if (j == TStar.length()) {
                return true;
            }
        }
        else {
            if (j != 0) {
                j = lps[j - 1];
            }
            else {
                i++;
            }
        }
    }

    return false;
}


int main() {
    std::string T, TStar;

    std::cout << ("insert a string") << std::endl;
    std::cin >> T;
    std::cout << ("insert a second string") << std::endl;
    std::cin >> TStar;
    

    if (isCyclicRotation(T, TStar)) {
        std::cout << T << " is a cycle of " << TStar << std::endl;
    }
    else {
        std::cout << T << " is not a cycle of " << TStar << std::endl;
    }

    return 0;
}