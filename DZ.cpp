#include <iostream>
#include <vector>
#include <string>
#include <algorithm>




// Функция для преобразования Барроуза-Уилера
std::string bwt(const std::string& input) {
    // Строка с добавленным специальным символом конца строки
    std::string s = input + '$';
    int n = s.size();

    // Вектор для хранения индексов всех циклических сдвигов
    std::vector<int> suffixArray(n);

    // Инициализация массива индексов
    for (int i = 0; i < n; ++i) {
        suffixArray[i] = i;
    }

    // Сортировка индексов по лексикографическому порядку циклических сдвигов
    std::sort(suffixArray.begin(), suffixArray.end(), [&s](int i, int j) {
        return s.substr(i) < s.substr(j);
        });

    // Формирование последнего столбца
    std::string result;
    for (int i = 0; i < n; ++i) {
        int idx = (suffixArray[i] - 1 + n) % n;  // индексы последнего столбца
        result.push_back(s[idx]);
    }

    return result;
}

// Основная функция
int main() {
    setlocale(LC_ALL, "Russian");
    std::string input;
    std::cout << "Введите строку для BWT: ";
    std::cin >> input;

    std::string transformed = bwt(input);
    std::cout << "Преобразование Барроуза-Уилера: " << transformed << std::endl;

    return 0;
}
