#include <iostream>
#include "bwt.h"

int main() {
    std::string input;
    std::cout << "������� ������ ��� BWT: ";
    std::cin >> input;

    std::string transformed = bwt(input);
    std::cout << "�������������� ��������-������: " << transformed << std::endl;

    return 0;
}
