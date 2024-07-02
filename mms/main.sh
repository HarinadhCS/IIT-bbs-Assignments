#!/bin/bash

# Compile and run bwt.cpp
g++ bwt.cpp -o bwt 
./bwt 

# Check if bwt_output is empty
if [ -s temp_bwt_output.txt ]; then

    # Create temp_dbr_input.txt using the bwt output
    cp temp_bwt_output.txt temp_dbr_input.txt

    # Compile and run dbr.cpp
    g++ dbr.cpp -o dbr
    ./dbr 

    # Check if dbr_output is empty
    if [ -s temp_dbr_output.txt ]; then

        # Compile and run vbr.cpp
        g++ vbr.cpp -o vbr
        ./vbr 

        # Check if vbr_output is empty
        if [ -s temp_vbr_output.txt ]; then

            # Compile and run rle.cpp
            g++ rle.cpp -o rle
            ./rle 

            # Check if rle_output is empty
            if [ -s temp_rle_output.txt ]; then

                # Compile and run huff.cpp
                g++ huff.cpp -o huff
                ./huff 

                # Check if huff_output is empty
                if [ -s temp_huff_output.txt ]; then

                    # Copy huff_output to output.txt
                    cat temp_huff_output.txt > output.txt

                else
                    echo "Error: temp_huff_output.txt is empty."
                fi
            else
                echo "Error: temp_rle_output.txt is empty."
            fi
        else
            echo "Error: temp_vbr_output.txt is empty."
        fi
    else
        echo "Error: temp_dbr_output.txt is empty."
    fi
else
    echo "Error: temp_bwt_output.txt is empty."
fi

g++ count.cpp -o count
./count


# Define the directories and file names for copying files
decompress_dir="decompress"
huffman_map_file="huffman_map.txt"
mappings_file="mappings.txt"
temp_huff_output_file="temp_huff_output.txt"

# Check if the decompress directory exists
if [ -d "$decompress_dir" ]; then
    # Copy contents from mms directory to decompress directory
    cp "$huffman_map_file" "$decompress_dir/$huffman_map_file"
    cp "$mappings_file" "$decompress_dir/$mappings_file"
    cp "$temp_huff_output_file" "$decompress_dir/huff_encoded_text.txt"

    echo "Files copied successfully."
else
    echo "Error: Decompress directory does not exist."
fi



