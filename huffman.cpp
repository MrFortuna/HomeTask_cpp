#include "huffman.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// Конструктор узла дерева
Node::Node(char ch, double prob) : character(ch), probability(prob), left(nullptr), right(nullptr) {}

// Оператор сравнения для очереди с приоритетом
bool CompareNode::operator()(Node* lhs, Node* rhs) {
    return lhs->probability > rhs->probability;
}

// Построение дерева Хаффмана
void buildHuffmanTree(vector<Node*>& nodes) {
    priority_queue<Node*, vector<Node*>, CompareNode> minHeap;
    for (auto node : nodes) {
        minHeap.push(node);
    }

    while (minHeap.size() > 1) {
        Node* left = minHeap.top(); minHeap.pop();
        Node* right = minHeap.top(); minHeap.pop();

        Node* internalNode = new Node('\0', left->probability + right->probability);
        internalNode->left = left;
        internalNode->right = right;

        minHeap.push(internalNode);
    }

    Node* root = minHeap.top();

    function<void(Node*, string)> generateCodes = [&](Node* node, string currentCode) {
        if (!node) return;
        if (node->character != '\0') {
            node->code = currentCode;
        }
        generateCodes(node->left, currentCode + "0");
        generateCodes(node->right, currentCode + "1");
    };

    generateCodes(root, "");
}

// Сжатие данных с использованием кодирования Хаффмана
string compressData(const string& data) {
    unordered_map<char, int> frequency;
    for (char ch : data) {
        frequency[ch]++;
    }

    vector<Node*> nodes;
    for (const auto& pair : frequency) {
        nodes.push_back(new Node(pair.first, static_cast<double>(pair.second) / data.size()));
    }

    buildHuffmanTree(nodes);

    unordered_map<char, string> huffmanCodes;
    for (auto node : nodes) {
        if (node->character != '\0') {
            huffmanCodes[node->character] = node->code;
        }
    }

    stringstream compressedText;
    for (char ch : data) {
        compressedText << huffmanCodes[ch];
    }

    ofstream dictFile("dict.txt");
    for (const auto& pair : huffmanCodes) {
        dictFile << "Symbol - " << pair.first << " :: Code - " << pair.second << "\n";
    }
    dictFile.close();

    return compressedText.str();
}
