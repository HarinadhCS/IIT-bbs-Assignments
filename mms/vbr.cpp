#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <sstream> // Added for stringstream

// Function to perform vertical byte reading
void verticalByteReading(const std::vector<std::bitset<8>> &bytes, std::ofstream &outputFile)
{
    int n = bytes.size(); // Number of bytes
    int bits = 8;         // Number of bits in a byte

    for (int i = bits - 1; i >= 0; --i)
    {
        for (int j = 0; j < n; ++j)
        {
            outputFile << bytes[j][i];
            if (j < n - 1)
            {
                outputFile << " "; // Add space between bytes
            }
        }
        outputFile << std::endl;
    }
}

int main()
{
    std::ifstream inputFile("temp_dbr_output.txt");
    std::ofstream outputFile("temp_vbr_output.txt");

    if (!inputFile.is_open())
    {
        std::cerr << "Error: Unable to open input file." << std::endl;
        return 1;
    }

    if (!outputFile.is_open())
    {
        std::cerr << "Error: Unable to open output file." << std::endl;
        return 1;
    }

    // Read bytes from the input file in the specified format
    std::vector<std::bitset<8>> bytes;
    std::string byte;
    while (inputFile >> byte)
    {
        // Convert the string of 8 bits to a bitset
        std::bitset<8> bits(byte);
        bytes.push_back(bits);
    }

    // Perform vertical byte reading
    verticalByteReading(bytes, outputFile);

    // Close the files
    inputFile.close();
    outputFile.close();

    return 0;
}
