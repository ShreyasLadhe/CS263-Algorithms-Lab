#include <iostream>

using namespace std;

const int MAX_CHAR = 6;

struct HuffmanNode {
    char data;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char data, int freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
};

void heapify(HuffmanNode* nodes[], int size, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size && nodes[left]->freq < nodes[smallest]->freq) {
        smallest = left;
    }

    if (right < size && nodes[right]->freq < nodes[smallest]->freq) {
        smallest = right;
    }

    if (smallest != index) {
        swap(nodes[index], nodes[smallest]);
        heapify(nodes, size, smallest);
    }
}

HuffmanNode* extractMin(HuffmanNode* nodes[], int& size) {
    HuffmanNode* minNode = nodes[0];
    nodes[0] = nodes[size - 1];
    size--;
    heapify(nodes, size, 0);
    return minNode;
}

void insert(HuffmanNode* nodes[], int& size, HuffmanNode* node) {
    size++;
    int i = size - 1;
    while (i > 0 && nodes[(i - 1) / 2]->freq > node->freq) {
        nodes[i] = nodes[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    nodes[i] = node;
}

HuffmanNode* buildHuffmanTree(char data[], int freq[], int n) {
    HuffmanNode* nodes[MAX_CHAR];

    for (int i = 0; i < n; i++) {
        nodes[i] = new HuffmanNode(data[i], freq[i]);
    }

    int size = n;

    for (int i = (size - 2) / 2; i >= 0; i--) {
        heapify(nodes, size, i);
    }

    while (size > 1) {
        HuffmanNode* left = extractMin(nodes, size);
        HuffmanNode* right = extractMin(nodes, size);

        HuffmanNode* newNode = new HuffmanNode('$', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;

        insert(nodes, size, newNode);
    }

    return nodes[0];
}

void printHuffmanCodes(HuffmanNode* root, string code, string huffmanCodes[]) {
    if (root == nullptr)
        return;

    if (root->data != '$')
        huffmanCodes[root->data - 'a'] = code;

    printHuffmanCodes(root->left, code + "0", huffmanCodes);
    printHuffmanCodes(root->right, code + "1", huffmanCodes);
}

int main() {
    char data[MAX_CHAR] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int freq[MAX_CHAR] = {3, 2, 6, 8, 2, 6};
    int n = sizeof(data) / sizeof(data[0]);

    HuffmanNode* root = buildHuffmanTree(data, freq, n);

    string huffmanCodes[MAX_CHAR];
    printHuffmanCodes(root, "", huffmanCodes);

    for (int i = 0; i < n; i++) {
        cout << data[i] << " : " << huffmanCodes[data[i] - 'a'] << endl;
    }

    return 0;
}