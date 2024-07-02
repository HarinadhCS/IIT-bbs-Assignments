#include <iostream>
#include <fstream>
#include <unordered_map>
#include <algorithm>
#include <bitset>
#include <cstring>
#include <vector>
std::unordered_map<char, std::string> byteMapping; // global one to acces it
void dynamicByteRemapping(const char *input, char *&output, std::unordered_map<char, std::string> &byteMapping)
{
    size_t len = std::strlen(input);

    output = new char[(len * 8) + (len - 1) + 1];

    size_t outputIndex = 0;
    for (size_t i = 0; i < len; ++i)
    {
        const std::string &mappedValue = byteMapping[input[i]];
        std::memcpy(output + outputIndex, mappedValue.c_str(), mappedValue.size());
        outputIndex += mappedValue.size();

        if (i < len - 1)
        {
            output[outputIndex++] = ' ';
        }
    }

    output[outputIndex] = '\0';
}

int main()
{
    std::ifstream inputFile("temp_dbr_input.txt");
    if (!inputFile.is_open())
    {
        std::cerr << "Error opening temp_dbr_input.txt" << std::endl;
        return 1;
    }

    std::string inputString;
    std::string line;
    while (std::getline(inputFile, line))
    {
        inputString += line;
    }

    // std::string inputString;
    // std::getline(inputFile, inputString);

    std::unordered_map<char, uint32_t> byteFrequency;
    for (size_t i = 0; i < std::strlen(inputString.c_str()); ++i)
    {
        byteFrequency[inputString[i]]++;
    }

    std::vector<std::pair<char, uint32_t>> sortedFrequency(byteFrequency.begin(), byteFrequency.end());
    std::sort(sortedFrequency.begin(), sortedFrequency.end(), [](const auto &a, const auto &b)
              {
                  if (a.second == b.second)
                  {
                      return a.first < b.first;
                  }
                  return a.second > b.second; });

    uint32_t mappingValue = 0;
    for (const auto &pair : sortedFrequency)
    {
        std::string mappedValue = std::bitset<8>(mappingValue++).to_string();
        byteMapping[pair.first] = mappedValue;
    }

    char *remappedOutput = nullptr;
    dynamicByteRemapping(inputString.c_str(), remappedOutput, byteMapping);

    std::ofstream outputFile("temp_dbr_output.txt");
    if (!outputFile.is_open())
    {
        std::cerr << "Error opening temp_dbr_output.txt" << std::endl;
        return 1;
    }

    outputFile << remappedOutput;

    std::ofstream outputFile2("mappings.txt");

    if (!outputFile2.is_open())
    {
        std::cerr << "Error opening output file." << std::endl;
        return 1;
    }

    for (const auto &pair : byteMapping)
    {
        outputFile2 << pair.first << ' ' << pair.second << '\n';
    }

    outputFile2.close();

    // std::cout << remappedOutput << std::endl;

    delete[] remappedOutput;

    return 0;
}
