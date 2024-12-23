#include "RLE_Agafonov.h"
#include <iostream>
#include <sstream>

std::string encodeRLE(const std::string& input) {
    setlocale(LC_ALL, "Russian");
    if (input.empty()) return "";

    std::string result;
    char currentChar = input[0];
    int count = 1;

    for (size_t i = 1; i < input.size(); ++i) {
        if (input[i] == currentChar) {
            count++;
        }
        else {
            result += std::to_string(count) + currentChar;
            currentChar = input[i];
            count = 1;
        }
    }

    result += std::to_string(count) + currentChar;

    return result;
}

std::string decodeRLE(const std::string& input) {
    setlocale(LC_ALL, "Russian");
    if (input.empty()) return "";

    std::string result;
    size_t index = 0;

    while (index < input.size()) {
        size_t numLength = 0;
        while (isdigit(input[index + numLength])) {
            numLength++;
        }

        int count = std::stoi(input.substr(index, numLength));

        for (int j = 0; j < count; ++j) {
            result.push_back(input[index + numLength]);
        }

        index += numLength + 1;
    }

    return result;
}
