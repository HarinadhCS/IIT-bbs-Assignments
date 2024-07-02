#include <iostream>
#include <string>
#include <map>
#include <fstream>

// Function to decode Huffman code using a map with variable-length codes
std::string decode_huffman_variable_length(const std::string& encoded_text,
                                           const std::map<std::string, char>& huffman_map) {
    std::string decoded_text;
    std::string current_code;

    for (char bit : encoded_text) {
        current_code += bit;

        // Check if the current code is in the Huffman map
        auto it = huffman_map.find(current_code);
        if (it != huffman_map.end()) {
            // Found a matching code, append the corresponding character to the decoded text
            decoded_text += it->second;
            current_code.clear();
        }
    }

    return decoded_text;
}

int main() {
    // Read the Huffman map from a text file
    std::ifstream huffman_map_file("huffman_map.txt");
    if (!huffman_map_file.is_open()) {
        std::cerr << "Error opening the Huffman map file!" << std::endl;
        return 1;
    }

    std::map<std::string, char> huffman_map;
    std::string code;
    char character;
    while (huffman_map_file >> code >> character) {
        huffman_map[code] = character;
    }
    huffman_map_file.close();

    // Read the encoded text from a text file
    std::ifstream encoded_text_file("huff_encoded_text.txt");
    if (!encoded_text_file.is_open()) {
        std::cerr << "Error opening the huff encoded text file!" << std::endl;
        return 1;
    }

    std::string encoded_text;
    std::getline(encoded_text_file, encoded_text);
    encoded_text_file.close();

    // Decode the Huffman variable-length encoded text
    std::string decoded_text = decode_huffman_variable_length(encoded_text, huffman_map);

    // Write the decoded text back to the text file
    std::ofstream output_file("huff_decoded_text.txt");
    if (!output_file.is_open()) {
        std::cerr << "Error opening the huff output file!" << std::endl;
        return 1;
    }

    output_file << decoded_text << std::endl;
    output_file.close();

    return 0;
}
