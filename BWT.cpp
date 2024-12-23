#include "bwt.h"
#include <vector>
#include <algorithm>
#include <unordered_map>

// Функция для преобразования Барроуза-Уилера
std::string bwt(const std::string& input) {
    std::string s = input + '$';
    int n = s.size();
    std::vector<int> suffixArray(n);

    for (int i = 0; i < n; ++i) {
        suffixArray[i] = i;
    }

    std::sort(suffixArray.begin(), suffixArray.end(), [&s](int i, int j) {
        return s.substr(i) < s.substr(j);
    });

    std::string result;
    for (int i = 0; i < n; ++i) {
        int idx = (suffixArray[i] - 1 + n) % n;
        result.push_back(s[idx]);
    }

    return result;
}

// Функция для декодирования строки, полученной с помощью BWT
std::string inverse_bwt(const std::string& bwt_string) {
    int n = bwt_string.size();
    std::string first_column = bwt_string;
    
    // Сортируем строку для первого столбца
    std::sort(first_column.begin(), first_column.end());

    // Массив, который будет хранить информацию о том, как индексы из last_column 
    // соответствуют индексам в first_column
    std::vector<int> next(n);

    // Маппинг символов между first_column и last_column
    std::unordered_map<char, std::vector<int>> first_column_char_positions;

    // Индексы символов в first_column
    for (int i = 0; i < n; ++i) {
        first_column_char_positions[first_column[i]].push_back(i);
    }

    // Маппинг индексов из last_column в first_column
    for (int i = 0; i < n; ++i) {
        next[i] = first_column_char_positions[bwt_string[i]].back();
        first_column_char_positions[bwt_string[i]].pop_back();
    }

    // Восстановление исходной строки
    std::string result;
    int row = 0;  // Начинаем с любой строки, например, с первой строки
    for (int i = 0; i < n - 1; ++i) {
        result += bwt_string[row];
        row = next[row];  // Переходим по индексу в next
    }

    std::reverse(result.begin(), result.end());
    return result;
}
