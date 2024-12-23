#ifndef BWT_H
#define BWT_H

#include <string>

// Функция для преобразования Барроуза-Уилера
std::string bwt(const std::string& input);

// Функция для декодирования строки, полученной с помощью BWT
std::string inverse_bwt(const std::string& bwt_string);

#endif // BWT_H
