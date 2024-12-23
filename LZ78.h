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
    // Êîíñòðóêòîð è äåñòðóêòîð
    LZ78Compressor();
    ~LZ78Compressor();

    // Îñíîâíîé ìåòîä äëÿ ñæàòèÿ è âîññòàíîâëåíèÿ äàííûõ
    void processCompressionAndDecompression(const std::string& input_filename,
        const std::string& compressed_filename,
        const std::string& decompressed_filename);

private:
    // Âñïîìîãàòåëüíûå ìåòîäû äëÿ ñæàòèÿ è âîññòàíîâëåíèÿ
    void compress(const std::string& message, const std::string& compressed_filename);
    void decompress(const std::string& compressed_filename, const std::string& decompressed_filename);
};

#endif // LZ78COMPRESSOR_H