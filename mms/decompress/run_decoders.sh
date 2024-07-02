#!/bin/bash

# Compile and run Huffman decoding
g++ -o huffmanDecode huffmanDecode.cpp
./huffmanDecode

# Compile and run RLE decoding
g++ -o RLE_decode RLE_decode.cpp
./RLE_decode

# Compile and run Vertical Byte Reading decoding
g++ -o VerticalByteReadingDecode VerticalByteReadingDecode.cpp
./VerticalByteReadingDecode

# Compile and run DBR decoding
g++ -o DBR_decode DBR_decode.cpp
./DBR_decode

# Compile and run BWT
g++ -o bwt bwt_decode.cpp
./bwt
