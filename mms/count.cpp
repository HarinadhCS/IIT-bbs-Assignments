#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>

int main()
{
    std::ifstream inputFile("temp_huff_output.txt");

    if (!inputFile.is_open())
    {
        std::cerr << "Error opening input file." << std::endl;
        return 1;
    }

    std::string content;
    char ch;
    while (inputFile.get(ch))
    {
        content += ch;
    }

    inputFile.close();

    int totalCharacters = content.size();
    int bitsToWrite = std::ceil(static_cast<double>(totalCharacters) / 8);

    std::ofstream outputFile("output.txt");

    if (!outputFile.is_open())
    {
        std::cerr << "Error opening output file." << std::endl;
        return 1;
    }

    // Seed for random number generation
    std::srand(static_cast<unsigned>(std::time(0)));

    for (int i = 0; i < bitsToWrite; ++i)
    {
        int randomBit = std::rand() % 2;
        outputFile << randomBit;
    }

    outputFile.close();

    // std::cout << "Successfully generated " << bitsToWrite << " random bits in output.txt." << std::endl;

    return 0;
}
