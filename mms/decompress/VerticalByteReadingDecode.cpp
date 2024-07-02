#include <iostream>
#include <vector>
#include <fstream>

std::string decode_vertical_byte_reading(const std::vector<std::string>& vertical_representation) {
    std::string decoded_text;

    int num_bits = vertical_representation[0].size();  // Assuming all strings have the same length

    for (int i = 0; i < num_bits; ++i) {
        for (const std::string& bit_vector : vertical_representation) {
            decoded_text += bit_vector[i];
        }
        decoded_text += ' ';  // Add a space after each set of characters
    }

    // Remove the last space
    if (!decoded_text.empty() && decoded_text.back() == ' ') {
        decoded_text.pop_back();
    }

    return decoded_text;
}

int main() {
    // Read vertical representation from a text file
    std::ifstream input_file("rle_decoded_text.txt");
    if (!input_file.is_open()) {
        std::cerr << "Error opening VERTICAL ENCODED file!" << std::endl;
        return 1;
    }

    std::vector<std::string> vertical_representation;
    std::string bit_vector;
    while (input_file >> bit_vector) {
        vertical_representation.push_back(bit_vector);
    }
    input_file.close();

    // Decode the vertical representation
    std::string decoded_text = decode_vertical_byte_reading(vertical_representation);

    // Write the decoded text back to the text file
    std::ofstream output_file("vertical_decoded_text.txt");
    if (!output_file.is_open()) {
        std::cerr << "Error opening the VERTICAL DECODED output file!" << std::endl;
        return 1;
    }

    output_file <<decoded_text << std::endl;
    output_file.close();

    return 0;
}
