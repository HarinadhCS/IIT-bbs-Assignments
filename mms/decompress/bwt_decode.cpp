#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

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
    // Read input text from a text file
    std::ifstream input_file("dbr_decoded_text.txt");
    if (!input_file.is_open())
    {
        std::cerr << "Error opening the bwt encoded file!" << std::endl;
        return 1;
    }

    std::string input_text;
    std::getline(input_file, input_text);
    input_file.close();

    // BWT encoding
    std::string bwt_result = bwt_encode(input_text);

    // Write the BWT encoded result and the reversed original text to the text file
    std::ofstream output_file("bwt_decoded_text.txt");
    if (!output_file.is_open())
    {
        std::cerr << "Error opening the bwt decoded output file!" << std::endl;
        return 1;
    }

    output_file << bwt_result << std::endl;

    // Reverse BWT
    std::string original_result = reverse_bwt(bwt_result);
    output_file << "Original Text: " << original_result << std::endl;

    output_file.close();

    return 0;
}
