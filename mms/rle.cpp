#include <iostream>
#include <fstream>
#include <cctype>

void modifiedRunLengthEncoding(const std::string &bits, std::ofstream &outputFile)
{
    int count = 1;
    for (size_t i = 1; i < bits.size(); ++i)
    {
        if (bits[i] == bits[i - 1])
        {
            // Increment count if consecutive bits are the same
            count = (count + 1); // Reset to 0 if count exceeds 255
            if (count == 255)
            {
                outputFile << count << " " << bits[i - 1] << " ";
                count = 0;
            }
        }
        else
        {
            // Write count and bit to the output file
            outputFile << count << " " << bits[i - 1] << " ";

            // Reset count to 1 for the new bit
            count = 1;
        }
    }

    // Write the last count and bit to the output file
    outputFile << count << " " << bits.back();
}

int main()
{
    std::ifstream inputFile("temp_vbr_output.txt");
    std::ofstream outputFile("temp_rle_output.txt");

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

    // Read entire content of the file into a string (excluding spaces)
    std::string fileContent;
    char c;
    while (inputFile.get(c))
    {
        if (std::isdigit(c))
        {
            fileContent += c;
        }
    }

    // Perform modified Run Length Encoding (RLE)
    modifiedRunLengthEncoding(fileContent, outputFile);

    // Close the files
    inputFile.close();
    outputFile.close();

    return 0;
}
