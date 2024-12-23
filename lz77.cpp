#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

// Структура для хранения сжатых данных
struct LZ77Tuple {
    int offset;  // Смещение
    int length;  // Длина
    char nextChar;  // Следующий символ
};

// Функция для сжатия данных с помощью алгоритма LZ77
void lz77CompressAndDecompress(const string& input) {
    int n = input.length();
    int maxWindowSize = 256;  // Размер окна поиска
    int maxCompressedSize = n;  // Максимальный размер сжатых данных

    // Массив для хранения сжимающих данных
    LZ77Tuple compressedData[maxCompressedSize];
    int outputIndex = 0;

    int i = 0;
    // Сжатие
    while (i < n) {
        int matchLength = 0;
        int matchIndex = -1;

        // Поиск наибольшего совпадения в текущем окне
        for (int j = max(0, i - maxWindowSize); j < i; j++) {  // Используем максимум 256 байт для сопоставления
            int k = 0;
            while (k < n - i && input[j + k] == input[i + k]) {
                k++;
            }
            if (k > matchLength) {
                matchLength = k;
                matchIndex = j;
            }
        }

        // Добавление результата в массив сжимающих данных
        if (matchLength > 0) {
            compressedData[outputIndex] = {matchIndex, matchLength, input[i + matchLength]};
            i += matchLength + 1; // Переход к следующему символу
        } else {
            compressedData[outputIndex] = {0, 0, input[i]};
            i++;
        }

        outputIndex++;
    }

    // Вывод сжатых данных в файл
    ofstream compressedFile("encoded_string.txt");
    if (compressedFile.is_open()) {
        for (int i = 0; i < outputIndex; i++) {
            compressedFile << "Алгоритм LZ77: " << "(" << compressedData[i].offset << ", " << compressedData[i].length << ", '" << compressedData[i].nextChar << "') ";
        }
        compressedFile.close();
    } else {
        cout << "Не удалось открыть файл для записи сжатой строки." << endl;
    }

    // Декодирование
    string decoded = "";
    for (int i = 0; i < outputIndex; i++) {
        if (compressedData[i].offset == 0 && compressedData[i].length == 0) {
            // Просто добавляем символ, если нет совпадений
            decoded += compressedData[i].nextChar;
        } else {
            // Восстанавливаем строку, используя смещение и длину
            int start = decoded.length() - compressedData[i].offset; // Начинаем с позиции, определяемой offset
            for (int j = 0; j < compressedData[i].length; j++) {
                decoded += decoded[start + j];  // Копируем символы из ранее восстановленной части
            }
            decoded += compressedData[i].nextChar;  // Добавляем следующий символ
        }
    }

    // Сохранение декодированной строки в файл
    ofstream decodedFile("decoded_string.txt");
    if (decodedFile.is_open()) {
        decodedFile << "Алгоритм LZ77: " + decoded;
        decodedFile.close();
    } else {
        cout << "Не удалось открыть файл для записи декодированной строки." << endl;
    }
}