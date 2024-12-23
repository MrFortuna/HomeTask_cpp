#include "Huffman.h"
#include <iostream>
#include <unordered_map>
#include <queue>
#include <functional>
#include <fstream>

namespace Huffman {
    // Узел дерева Хаффмана
    struct Node {
        char ch;
        int freq;
        Node* left;
        Node* right;

        Node(char character, int frequency, Node* l = nullptr, Node* r = nullptr)
            : ch(character), freq(frequency), left(l), right(r) {}
    };

    // Компаратор для очереди с приоритетами
    struct comp {
        bool operator()(Node* l, Node* r) {
            return l->freq > r->freq;
        }
    };

    void run(const std::string& text) {
        // Подсчёт частоты каждого символа
        std::unordered_map<char, int> freq;
        for (char ch : text) {
            freq[ch]++;
        }

        // Очередь с приоритетами для построения дерева Хаффмана
        std::priority_queue<Node*, std::vector<Node*>, comp> pq;
        for (const auto& pair : freq) {
            pq.push(new Node(pair.first, pair.second));
        }

        // Построение дерева Хаффмана
        while (pq.size() > 1) {
            Node* left = pq.top(); pq.pop();
            Node* right = pq.top(); pq.pop();
            int sum = left->freq + right->freq;
            pq.push(new Node('\0', sum, left, right));
        }
        Node* root = pq.top();

        // Построение таблицы кодов Хаффмана
        std::unordered_map<char, std::string> huffmanCode;
        std::function<void(Node*, std::string)> encode = [&](Node* node, std::string str) {
            if (!node) return;
            if (!node->left && !node->right) {
                huffmanCode[node->ch] = str;
            }
            encode(node->left, str + "0");
            encode(node->right, str + "1");
            };
        encode(root, "");

        // Запись кодов Хаффмана в файл
        std::ofstream outFile("huffman_codes.txt");
        if (outFile.is_open()) {
            outFile << "Huffman Codes are:\n";
            for (const auto& pair : huffmanCode) {
                outFile << pair.first << ": " << pair.second << "\n";
            }
            outFile.close();
        }
        else {
            std::cerr << "Unable to open file for writing\n";
            return;
        }

        // Кодирование строки
        std::string encoded = "";
        for (char ch : text) {
            encoded += huffmanCode[ch];
        }

        // Запись закодированной строки в файл
        outFile.open("encoded_string.txt");
        if (outFile.is_open()) {
            outFile << "\nEncoded string is:\n" << encoded << "\n";
            outFile.close();
        }
        else {
            std::cerr << "Unable to open file for writing\n";
            return;
        }

        // Декодирование строки
        std::string decoded = "";
        Node* current = root;
        for (char bit : encoded) {
            current = (bit == '0') ? current->left : current->right;
            if (!current->left && !current->right) {
                decoded += current->ch;
                current = root;
            }
        }

        // Запись раскодированной строки в файл
        outFile.open("decoded_string.txt");
        if (outFile.is_open()) {
            outFile << "\nDecoded string is:\n" << decoded << "\n";
            outFile.close();
        }
        else {
            std::cerr << "Unable to open file for writing\n";
            return;
        }

        // Очистка памяти
        std::function<void(Node*)> freeTree = [&](Node* node) {
            if (!node) return;
            freeTree(node->left);
            freeTree(node->right);
            delete node;
            };
        freeTree(root);
    }
}
