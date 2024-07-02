#include <iostream>
#include <vector>
#include <fstream>

std::string simple_decode(const std::vector<int>& encoded_data) {
    std::string decoded_text;
    int bit_count = 0;
    char current_char = '0';  // Initialize current_char

    for (int i = 0; i < encoded_data.size(); i+=2) {
        int run_length = encoded_data[i];
        int val = encoded_data[i+1];
        current_char = (val == 1) ? '1' : '0';

        for (int j = 0; j < run_length; ++j) {
            decoded_text += current_char;
            if ((++bit_count) % 6 == 0) {
                decoded_text += '\n';  // Add a space after every 6 bits except the last one
            }
        }

    }

    return decoded_text;
}

int main() {
    // Read encoded data from the text file
    std::ifstream input_file("huff_decoded_text.txt");
    if (!input_file.is_open()) {
        std::cerr << "Error opening RLE ENCODED file!" << std::endl;
        return 1;
    }

    std::vector<int> encoded_data;
    int value;
    while (input_file >> value) {
        encoded_data.push_back(value);
    }
    input_file.close();

    // Decode the data
    std::string decoded_text = simple_decode(encoded_data);

    // Write the decoded text back to the text file
    std::ofstream output_file("rle_decoded_text.txt");
    if (!output_file.is_open()) {
        std::cerr << "Error opening RLE DECODED file!" << std::endl;
        return 1;
    }

    output_file << decoded_text << std::endl;
    output_file.close();

    return 0;
}
