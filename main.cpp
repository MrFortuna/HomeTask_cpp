#include "arithmetic_coding.cpp"
#include "BWT.cpp"
#include "LZ78.cpp"
#include "RLE_Agafonov.cpp"
#include "LZW.cpp"
#include "HUFFMANn.cpp"
#include "huffman.cpp"
#include "lz77.cpp"
#include <iostream>
#include <fstream>
#include <string>


void writeToFiles(const std::string& method_name, const std::string& compressed_string, const std::string& decompressed_string) {

    std::ofstream file1("encoded_string.txt");
    if (file1.is_open()) {
        file1 << "Method name: " << method_name << "\n\n";
        file1 << compressed_string;
        file1.close();
    } else {
        std::cerr << "Не удалось открыть encoded_string.txt для записи.\n";
    }

    std::ofstream file2("decoded_string.txt");
    if (file2.is_open()) {
        file2 << "Method name: " << method_name << "\n\n";
        file2 << decompressed_string;
        file2.close();
    }
    else {
        std::cerr << "Не удалось открыть decoded_string.txt для записи.\n";
    }
}

int main() {
    LZ78Compressor compressorLZ78;
    LZW compressorLZW;
    int method;

    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Не удалось открыть файл для чтения." << endl;
        return 1;
    }
    string original_text;
    string line;

    while (getline(inputFile, line)) {
        original_text += line + "\n";
    }
    inputFile.close();

    while (true) {
        std::cout << "1. Кодировка Хаффмана" << std::endl;
        std::cout << "2. Алгоритм LZW" << std::endl;
        std::cout << "3. Алгоритм RLE" << std::endl;
        std::cout << "4. Алгоритм BWT" << std::endl;
        std::cout << "5. Алгоритм Шеннона-Фано" << std::endl;
        std::cout << "6. Алгоритм LZ78" << std::endl;
        std::cout << "7. Арифметическое кодирование" << std::endl;
        std::cout << "8. Алгоритм LZ77" << std::endl;
        std::cin >> method;

        if (method == 0){
            break;
        }

        switch(method){
            case 1: {
                Huffman::run(original_text);
                break;
            }
            case 2: {
                std::string coded = compressorLZW.compression(original_text);
                std::string decoded = compressorLZW.decompression(coded);

                writeToFiles("Алгоритм LZW", coded, decoded);
                break;
            }
            case 3: {
                std::string coded = encodeRLE(original_text);
                std::string decoded = decodeRLE(coded);

                writeToFiles("Алгоритм RLE", coded, decoded);
                break;
            }
            case 4: {
                std::string bwt_str1 = bwt(original_text);
                std::string decoded_str1 = inverse_bwt(bwt_str1);

                writeToFiles("Алгоритм BWT", bwt_str1, decoded_str1);
                break;
            }
            case 5: {
                string coded = compressData(original_text);
                string decoded = "не декодирует";

                writeToFiles("Алгоритм Шеннона-Фано", coded, decoded);
                break;
            }
            case 6: {
                compressorLZ78.processCompressionAndDecompression("input.txt", "encoded_string.txt", "decoded_string.txt");
                break;
            }
            case 7: {
                auto coded_a =  code_to_arithmetic(original_text);

                cout << coded_a.second << endl;
                std::string decoded = decode_from_arithmetic(coded_a.first, coded_a.second);

                writeToFiles("Арифметическое кодирование", coded_a.second, decoded);
                break;
            }
            case 8: {
                lz77CompressAndDecompress(original_text);

                break;
            }
        }
    }
    return 0;
}