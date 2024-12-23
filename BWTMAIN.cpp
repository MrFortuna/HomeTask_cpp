#include <iostream>
#include "bwt.h"

int main() {
    std::string input;
    std::cout << "Введите строку для BWT: ";
    std::cin >> input;

    std::string transformed = bwt(input);
    std::cout << "Преобразование Барроуза-Уилера: " << transformed << std::endl;

    return 0;
}
