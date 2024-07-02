#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

// Function to perform BWT encoding
std::string bwt_encode(const std::string &input)
{
    std::vector<std::string> rotations;
    size_t len = input.length();

    // Create rotations and store them in a vector
    for (size_t i = 0; i < len; ++i)
    {
        rotations.push_back(input.substr(i) + input.substr(0, i));
    }

    // Sort the rotations lexicographically
    std::sort(rotations.begin(), rotations.end());

    // Extract the last characters of each rotation to obtain BWT
    std::string bwt;
    for (const auto &rotation : rotations)
    {
        bwt += rotation.back();
    }

    return bwt;
}

// Function to perform reverse BWT
std::string reverse_bwt(const std::string &bwt)
{
    size_t len = bwt.length();
    std::vector<std::pair<char, size_t>> indexed_bwt(len);

    // Assign indices to each character in the BWT
    for (size_t i = 0; i < len; ++i)
    {
        indexed_bwt[i] = std::make_pair(bwt[i], i);
    }

    // Sort the characters along with their indices
    std::sort(indexed_bwt.begin(), indexed_bwt.end());

    // Reconstruct the original string
    std::string original(len, ' ');
    size_t index = indexed_bwt[0].second;
    for (size_t i = 0; i < len; ++i)
    {
        original[i] = indexed_bwt[index].first;
        index = indexed_bwt[index].second;
    }

    return original;
}

int main()
{
    // Read input from file
    std::ifstream inputFile("bwt_input.txt");
    if (!inputFile.is_open())
    {
        std::cerr << "Error opening bwt_input.txt" << std::endl;
        return 1;
    }

    // Read the entire content of the file into a string
    std::string input_text;
    std::string line;
    while (std::getline(inputFile, line))
    {
        input_text += line;
    }

    // BWT encoding
    std::string bwt_result = bwt_encode(input_text);
    // std::cout << bwt_result << std::endl;

    // Reverse BWT
    // std::string original_result = reverse_bwt(bwt_result);
    // std::cout << "Original Text: " << original_result << std::endl;

    // Write to files
    std::ofstream bwtOutputFile("temp_bwt_output.txt");
    if (bwtOutputFile.is_open())
    {
        bwtOutputFile << bwt_result;
        bwtOutputFile.close();
        // std::cout << "BWT result written to temp_bwt_output.txt" << std::endl;
    }
    else
    {
        std::cerr << "Error opening temp_bwt_output.txt" << std::endl;
    }

    // std::ofstream originalOutputFile("testtext.txt");
    // if (originalOutputFile.is_open())
    // {
    //     originalOutputFile << original_result;
    //     originalOutputFile.close();
    //     std::cout << "Original result written to testtext.txt" << std::endl;
    // }
    // else
    // {
    //     std::cerr << "Error opening testtext.txt" << std::endl;
    // }

    return 0;
}
