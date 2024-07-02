#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>

// Function to decode SDBR using dynamic byte remapping
std::string decode_dynamic_byte_remapping(const std::string& sdbr,
                                          const std::unordered_map<char, std::string>& mappings) {
    std::string decoded_text;

    // Remove spaces from the input SDBR
    std::string sanitized_sdbr;
    for (char c : sdbr) {
        if (c != ' ') {
            sanitized_sdbr += c;
        }
    }

    // Iterate over sanitized SDBR with a step of the length of each mapped value
    for (size_t i = 0; i < sanitized_sdbr.size(); i += mappings.begin()->second.size()) {
        // Extract the substring corresponding to a mapped value
        std::string substring = sanitized_sdbr.substr(i, mappings.begin()->second.size());

        // Reverse lookup the mapping to find the character
        for (const auto& mapping : mappings) {
            if (mapping.second == substring) {
                decoded_text += mapping.first;
                break;
            }
        }
    }

    return decoded_text;
}

int main() {
    // Read encoded input SDBR and mappings from text files
    std::ifstream sdbr_file("vertical_decoded_text.txt");
    if (!sdbr_file.is_open()) {
        std::cerr << "Error opening the SDBR file!" << std::endl;
        return 1;
    }

    std::string sdbr;
    std::getline(sdbr_file, sdbr);
    sdbr_file.close();

    std::unordered_map<char, std::string> mappings;
    std::ifstream mappings_file("mappings.txt");
    if (!mappings_file.is_open()) {
        std::cerr << "Error opening the mappings file!" << std::endl;
        return 1;
    }

    char character;
    std::string mapping;
    while (mappings_file >> character >> mapping) {
        mappings[character] = mapping;
    }
    mappings_file.close();

    // Decode the SDBR
    std::string decoded_text = decode_dynamic_byte_remapping(sdbr, mappings);

    // Write the decoded text back to the text file
    std::ofstream output_file("dbr_decoded_text.txt");
    if (!output_file.is_open()) {
        std::cerr << "Error opening the SDBR output file!" << std::endl;
        return 1;
    }

    output_file << decoded_text << std::endl;
    output_file.close();

    return 0;
}
