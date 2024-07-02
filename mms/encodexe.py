def encode_binary_to_text(binary_file_path, output_text_file):
    try:
        # Open the binary file
        with open(binary_file_path, 'rb') as binary_file:
            # Read binary data from the file
            binary_data = binary_file.read()

            # Convert binary data to a hexadecimal string
            hex_string = binary_data.hex()

            # Write the encoded text to a file
            with open(output_text_file, 'w') as text_file:
                text_file.write(hex_string)

        print(f"Binary data encoded and written to {output_text_file}")

    except Exception as e:
        print(f"Error: {e}")

# Example usage for an executable file
encode_binary_to_text('input.exe', 'bwt_input.txt')


# decode

# def decode_text_to_binary(text_file_path, output_binary_file):
#     try:
#         # Read the text data from the file
#         with open(text_file_path, 'r') as text_file:
#             hex_string = text_file.read()

#         # Convert the hexadecimal string to binary data
#         binary_data = bytes.fromhex(hex_string)

#         # Write the binary data to a file
#         with open(output_binary_file, 'wb') as binary_file:
#             binary_file.write(binary_data)

#         print(f"Text decoded and written to {output_binary_file}")

#     except Exception as e:
#         print(f"Error: {e}")

# # Example usage
# decode_text_to_binary('bwt_input.txt', 'decoded_input.exe')
