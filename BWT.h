#ifndef BWT_H
#define BWT_H

#include <string>

// ������� ��� �������������� ��������-������
std::string bwt(const std::string& input);

// ������� ��� ������������� ������, ���������� � ������� BWT
std::string inverse_bwt(const std::string& bwt_string);

#endif // BWT_H
