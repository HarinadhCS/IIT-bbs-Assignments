#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <bitset>
#include <sstream>
#include <queue>
// #include "common.h"
using namespace std;

// Global map to store Huffman codes
std::map<int, std::string> huffmanCodeMap;

// Structure for a node in the Huffman tree
struct HuffmanNode
{
    int intValue;
    int frequency;
    HuffmanNode *left;
    HuffmanNode *right;

    HuffmanNode(int val, int freq) : intValue(val), frequency(freq), left(nullptr), right(nullptr) {}
};

// Comparison function for priority queue
struct CompareNodes
{
    bool operator()(HuffmanNode *lhs, HuffmanNode *rhs) const
    {
        return lhs->frequency > rhs->frequency;
    }
};

// Function to generate Huffman tree and return the root
HuffmanNode *buildHuffmanTree(const std::map<int, int> &valueFrequency)
{
    std::priority_queue<HuffmanNode *, std::vector<HuffmanNode *>, CompareNodes> minHeap;

    // Create leaf nodes for each value and add to min heap
    for (const auto &entry : valueFrequency)
    {
        minHeap.push(new HuffmanNode(entry.first, entry.second));
    }

    // Build Huffman tree
    while (minHeap.size() > 1)
    {
        HuffmanNode *left = minHeap.top();
        minHeap.pop();

        HuffmanNode *right = minHeap.top();
        minHeap.pop();

        HuffmanNode *internalNode = new HuffmanNode(0, left->frequency + right->frequency);
        internalNode->left = left;
        internalNode->right = right;

        minHeap.push(internalNode);
    }

    return minHeap.top();
}

// Recursive function to traverse Huffman tree and generate prefix codes
void generateHuffmanCodes(HuffmanNode *root, std::string code)
{
    if (root)
    {
        if (root->left == nullptr && root->right == nullptr)
        {
            huffmanCodeMap[root->intValue] = code;
        }

        generateHuffmanCodes(root->left, code + "0");
        generateHuffmanCodes(root->right, code + "1");
    }
}

int main()
{
    std::ifstream inputFile("temp_rle_output.txt");

    if (!inputFile.is_open())
    {
        std::cerr << "Error: Unable to open input file." << std::endl;
        return 1;
    }

    // Read input from file
    std::map<int, int> valueFrequency;
    int value;
    while (inputFile >> value)
    {
        valueFrequency[value]++;
    }

    if (valueFrequency.empty())
    {
        std::cerr << "Error: Input file is empty." << std::endl;
        return 1;
    }

    // Build Huffman tree
    HuffmanNode *huffmanTree = buildHuffmanTree(valueFrequency);

    // Generate Huffman codes
    generateHuffmanCodes(huffmanTree, "");

    // Close the file
    inputFile.close();

    // Write Huffman-encoded bits to temp_huff_output.txt
    std::ofstream outputFile("temp_huff_output.txt");
    if (outputFile.is_open())
    {
        inputFile.open("temp_rle_output.txt");

        while (inputFile >> value)
        {
            outputFile << huffmanCodeMap[value];
        }

        inputFile.close();
        outputFile.close();
    }
    else
    {
        std::cerr << "Error: Unable to open output file." << std::endl;
        return 1;
    }

    std::ofstream outputFile2("huffman_map.txt");

    if (!outputFile2.is_open())
    {
        std::cerr << "Error opening output file." << std::endl;
        return 1;
    }

    for (const auto &pair : huffmanCodeMap)
    {
        outputFile2 << pair.first << ' ' << pair.second << '\n';
    }

    outputFile2.close();

    // for (auto i = huffmanCodeMap.begin(); i != huffmanCodeMap.end(); i++)
    // {

    //     cout << i->first << " " << i->second << endl;
    // }

    return 0;
}
