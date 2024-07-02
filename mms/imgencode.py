from PIL import Image

def encode_image_to_text(image_path, output_text_file):
    try:
        # Open the image file
        with Image.open(image_path) as img:
            # Convert the image to a list of pixel values
            pixel_values = list(img.getdata())

            # Convert the pixel values to a string
            image_text = ' '.join(str(pixel) for pixel in pixel_values)

            # Write the encoded text to a file
            with open(output_text_file, 'w') as text_file:
                text_file.write(image_text)

        print(f"Image encoded and written to {output_text_file}")

    except Exception as e:
        print(f"Error: {e}")

# Example usage
encode_image_to_text('input.jpg', 'bwt_input.txt')

