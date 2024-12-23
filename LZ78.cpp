#include "LZ78.h"

LZ78Compressor::LZ78Compressor() {
    // Конструктор (можно использовать для инициализации, если нужно)
}

LZ78Compressor::~LZ78Compressor() {
    // Деструктор (можно использовать для очистки ресурсов, если нужно)
}

void LZ78Compressor::processCompressionAndDecompression(const std::string& input_filename,
    const std::string& compressed_filename,
    const std::string& decompressed_filename) {
    // Чтение исходного сообщения из файла
    std::ifstream input_file(input_filename);
    std::stringstream buffer;
    buffer << input_file.rdbuf();
    std::string message = buffer.str();

    // Сжатие строки
    compress(message, compressed_filename);

    // Восстановление сообщения из сжатых данных
    decompress(compressed_filename, decompressed_filename);
}

void LZ78Compressor::compress(const std::string& message, const std::string& compressed_filename) {
    std::map<std::string, int> storage;
    std::vector<std::pair<int, char>> compressed_data;
    std::string current_symbol = "";
    int index = 1;

    for (char symbol : message) {
        current_symbol += symbol;
        if (storage.find(current_symbol) == storage.end()) {
            storage[current_symbol] = index;
            if (!current_symbol.empty()) {
                compressed_data.push_back(std::make_pair(storage[current_symbol.substr(0, current_symbol.length() - 1)], symbol));
            }
            index += 1;
            current_symbol = "";
        }
    }

    // Запись сжатого сообщения в файл
    std::ofstream output_file(compressed_filename);
    for (const auto& element : compressed_data) {
        output_file << "(" << element.first << ", " << element.second << "), ";
    }
    output_file.close();
}

void LZ78Compressor::decompress(const std::string& compressed_filename, const std::string& decompressed_filename) {
    // Чтение сжатого файла
    std::ifstream input_file(compressed_filename);
    std::string compressed_data_str;
    std::getline(input_file, compressed_data_str);

    // Разбор сжатого сообщения (предполагается, что оно записано в формате: (index, char), ...)
    std::vector<std::pair<int, char>> compressed_data;
    std::stringstream ss(compressed_data_str);
    char ch;
    int idx;
    while (ss >> ch) {
        if (ch == '(') {
            ss >> idx >> ch; // Пропускаем запятую
            char symbol;
            ss >> symbol;
            ss >> ch; // Закрывающая скобка
            compressed_data.push_back({ idx, symbol });
        }
    }

    // Восстановление сообщения
    std::map<int, std::string> storage_for_decompression;
    std::string decompressed_data = "";
    int index = 1;

    for (const auto& symbol : compressed_data) {
        storage_for_decompression[index] = storage_for_decompression[symbol.first] + symbol.second;
        decompressed_data += storage_for_decompression[index];
        index += 1;
    }

    // Запись восстановленного сообщения в файл
    std::ofstream decompressed_file(decompressed_filename);
    decompressed_file << decompressed_data;
    decompressed_file.close();
}

