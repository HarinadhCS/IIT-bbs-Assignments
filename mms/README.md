## MutliMedia Systems Assignment
- paper link : https://arxiv.org/abs/2101.05329
- Improving Run Length Encoding by Preprocessing
- The above paper is about data compression.
-  we have followed the techniques proposed in the papaer and got similar results using text data.

## How to Run for Compression:

1. **Prepare Input:**
   - After unzipping, locate the text file named `bwt_input.txt`.
   - Replace its contents with the text you want to compress, or paste your text directly into this file.
   - Remove any existing content in `bwt_input.txt`.

2. **Execute Compression:**
   - Run the shell script `main.sh` using the command:
     ```
     ./main.sh
     ```

3. **Access Compressed Output:**
   - The compressed output will be saved in `output.txt`.

4. **Compare File Sizes:**
   - Compare the sizes of `bwt_input.txt` (original text file) and `output.txt` (compressed file).

5. **Compression Results:**
   - The size of `output.txt` will typically be smaller than `bwt_input.txt`, showcasing compression effectiveness.

6. **Detailed Steps:**
   - The compression flow:
     ```
     bwt_input.txt -> temp_bwt_output.txt -> temp_dbr_output.txt -> temp_vbr_output.txt -> temp_rle_output.txt -> temp_huff_output.txt
     ```
   - Each file (`temp_*.txt`) represents an intermediate step in the compression process.

## How to Run for Decompression:

1. **Navigate to Decompression:**
   - Go to the decompress folder.

2. **Execute Decompression:**
   - Run the shell script named `run_decoders.sh`.

## Compression Statistics:

- **Input File Size:**
  - `bwt_input.txt` (input file): 9774 bytes.

- **Output File Size (after Compression):**
  - `output.txt`: 1668 bytes.

- **Compression Ratio:**
  - \( \text{Compression Ratio} = \frac{9774}{1668} \approx 7.27 \).

- **Improvement Percentage:**
  - \( \text{Improvement Percentage} = \left( \frac{9774 - 1668}{9774} \right) \times 100 \approx 87\% \).

## Note on Handling Images and .exe Files:

- Compression support exists for `.jpg` image files and `.exe` files.
- Converting these contents to text files for compression can be time-consuming.

