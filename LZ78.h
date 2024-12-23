#pragma once

#ifndef LZ78COMPRESSOR_H
#define LZ78COMPRESSOR_H

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>

class LZ78Compressor {
public:
    // ����������� � ����������
    LZ78Compressor();
    ~LZ78Compressor();

    // �������� ����� ��� ������ � �������������� ������
    void processCompressionAndDecompression(const std::string& input_filename,
        const std::string& compressed_filename,
        const std::string& decompressed_filename);

private:
    // ��������������� ������ ��� ������ � ��������������
    void compress(const std::string& message, const std::string& compressed_filename);
    void decompress(const std::string& compressed_filename, const std::string& decompressed_filename);
};

#endif // LZ78COMPRESSOR_H
