#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <utility>  // Для std::pair

using namespace std;
void printLongDouble(long double value);
pair<map<long double, string>, string> code_to_arithmetic(string a);
string decode_from_arithmetic (map<long double, string> keys, string a);