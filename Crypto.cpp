#include "Crypto.h"
#include "GrayscaleImage.h"

// Extract the least significant bits (LSBs) from SecretImage, calculating x, y based on message length
std::vector<int> Crypto::extract_LSBits(SecretImage& secret_image, int message_length) {
    std::vector<int> LSB_array;
    // TODO: Your code goes here.

    // 1. Reconstruct the SecretImage to a GrayscaleImage.
    // 2. Calculate the image dimensions.
    // 3. Determine the total bits required based on message length.
    // 4. Ensure the image has enough pixels; if not, throw an error.
    // 5. Calculate the starting pixel from the message_length knowing that
    //    the last LSB to extract is in the last pixel of the image.
    // 6. Extract LSBs from the image pixels and return the result.


    GrayscaleImage reconstructed_image = secret_image.reconstruct();

    int width = reconstructed_image.get_width();
    int height = reconstructed_image.get_height();
    int total_pixels = width * height;






    if(message_length > total_pixels) {
        throw std::length_error("Message length too large");
    }





    int start_pixel_index = total_pixels - message_length*7;

    // 6. Extract LSBs from the image pixels
    for (int i = 0; i < message_length*7; ++i) {
        // Get the current pixel's value
        int pixel_value = reconstructed_image.get_pixel((start_pixel_index + i) / width, (start_pixel_index + i) % width);

        // Extract the LSB
        int LSB = pixel_value & 1;

        // Add the LSB to the array
        LSB_array.push_back(LSB);
    }

    return LSB_array;
}


// Decrypt message by converting LSB array into ASCII characters
std::string Crypto::decrypt_message(const std::vector<int>& LSB_array) {
    std::string message;
    // TODO: Your code goes here.

    // 1. Verify that the LSB array size is a multiple of 7, else throw an error.
    // 2. Convert each group of 7 bits into an ASCII character.
    // 3. Collect the characters to form the decrypted message.
    // 4. Return the resulting message.

    if (LSB_array.size() % 7 != 0) {
        throw std::runtime_error("ERROR : LSB array size is not a multiple of 7");
    }

    for (size_t i = 0; i < LSB_array.size(); i += 7) {
        std::bitset<7> bits;


        for (int j = 0; j < 7; ++j) {
            bits[6 - j] = LSB_array[i + j];
        }


        char c = static_cast<char>(bits.to_ulong());


        message += c;
    }

    return message;
}

// Encrypt message by converting ASCII characters into LSBs
std::vector<int> Crypto::encrypt_message(const std::string& message) {
    std::vector<int> LSB_array;
    // TODO: Your code goes here.

    // 1. Convert each character of the message into a 7-bit binary representation.
    //    You can use std::bitset.
    // 2. Collect the bits into the LSB array.
    // 3. Return the array of bits.

    for(int i = 0;  i < message.length(); ++i) {
        std::bitset<7> bits(message[i]);
        for (int j = 6; j >= 0; --j) {
            LSB_array.push_back(bits[j]);

        }
    }


    return LSB_array;
}

// Embed LSB array into GrayscaleImage starting from the last bit of the image
SecretImage Crypto::embed_LSBits(GrayscaleImage& image, const std::vector<int>& LSB_array) {

    // TODO: Your code goes here.

    // 1. Ensure the image has enough pixels to store the LSB array, else throw an error.
    // 2. Find the starting pixel based on the message length knowing that
    //    the last LSB to embed should end up in the last pixel of the image.
    // 3. Iterate over the image pixels, embedding LSBs from the array.
    // 4. Return a SecretImage object constructed from the given GrayscaleImage
    //    with the embedded message.


    int width = image.get_width();
    int height = image.get_height();
    int total_pixels = width * height;
    int message_length = LSB_array.size();
    int start_pixel_index = total_pixels - message_length;


    if(message_length > total_pixels) {
        throw std::length_error("Message length too large");
    }


    int lsb_index = 0;



    // Embed LSBs into the image starting from the calculated start_pixel_index
    for (int i = start_pixel_index; i < total_pixels; ++i) {
        int row = i / width;
        int col = i % width;
        int pixel_value = image.get_pixel(row, col);


        if(lsb_index >= message_length) {
            break;
        }

        if(LSB_array[lsb_index] == 1) {
            pixel_value |=1;
        }
        else {
            pixel_value &= ~1;
        }

        image.set_pixel(row, col, pixel_value);
        lsb_index++;
    }




    SecretImage secret_image(image);

    return secret_image;
}
