#include <iostream>
#include <vector>
#include <string>
#include <tuple>

using namespace std;

// Структура для хранения сжатых данных
struct LZ77Tuple {
    int offset; // Смещение
    int length; // Длина
    char nextChar; // Следующий символ
};

// Функция для сжатия данных с помощью алгоритма LZ77
vector<LZ77Tuple> lz77Compress(const string& input) {
    vector<LZ77Tuple> output;
    int n = input.length();
    int i = 0;

    while (i < n) {
        int matchLength = 0;
        int matchIndex = -1;

        // Поиск наибольшего совпадения в текущем окне
        for (int j = max(0, i - 256); j < i; j++) { // Используем максимум 256 байт для сопоставления
            int k = 0;
            while (k < n - i && input[j + k] == input[i + k]) {
                k++;
            }
            if (k > matchLength) {
                matchLength = k;
                matchIndex = j;
            }
        }

        // Добавление результата в выходной вектор
        if (matchLength > 0) {
            output.push_back({matchIndex, matchLength, input[i + matchLength]});
            i += matchLength + 1; // Переход к следующему символу
        } else {
            output.push_back({0, 0, input[i]});
            i++;
        }
    }

    return output;
}

// Функция для вывода сжатых данных
void printCompressed(const vector<LZ77Tuple>& compressed) {
    for (const auto& t : compressed) {
        cout << "(" << t.offset << ", " << t.length << ", '" << t.nextChar << "') ";
    }
    cout << endl;
}

int main() {
    string input;
    cout << "Введите строку для сжатия: ";
    getline(cin, input);

    vector<LZ77Tuple> compressed = lz77Compress(input);
    cout << "Сжатая строка: ";
    printCompressed(compressed);

    return 0;
}
