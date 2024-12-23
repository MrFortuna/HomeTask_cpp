#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <functional>

// Узел дерева Хаффмана
struct Node {
    char character;
    double probability;
    std::string code;
    Node* left;
    Node* right;

    Node(char ch, double prob);
};

// Сравнение узлов для очереди с приоритетом
struct CompareNode {
    bool operator()(Node* lhs, Node* rhs);
};

// Построение дерева Хаффмана
void buildHuffmanTree(std::vector<Node*>& nodes);

// Сжатие данных с использованием кодирования Хаффмана
std::string compressData(const std::string& data);

#endif // HUFFMAN_H