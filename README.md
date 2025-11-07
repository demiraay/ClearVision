# ClearVision  
**Project:** ClearVision — Vision Beyond the Visible  

##  Overview  
ClearVision is an image processing project that enhances grayscale images and embeds secret messages into them.  
It simulates defense-grade image enhancement and steganography systems using filters, matrix operations, and bit-level message encryption.

##  Features  
- **Mean Filter:** Smooths and denoises grayscale images.  
- **Gaussian Filter:** Applies weighted blurring while preserving details.  
- **Unsharp Masking:** Sharpens edges and improves clarity.  
- **Image Operations:** Supports image addition, subtraction, and equality comparison through operator overloading.  
- **Secret Image Handling:** Splits images into upper and lower triangular matrices for secure storage.  
- **Crypto Module:** Embeds and extracts messages via Least Significant Bit (LSB) manipulation.

##  Technologies  
- **Language:** C++11  
- **Libraries:** `stb_image.h`, `stb_image_write.h`  
- **Concepts:** Dynamic Memory Allocation, Operator Overloading, File I/O, Bitwise Operations  

## 🗂️ Project Structure  

├── Crypto.cpp / Crypto.h
├── Filter.cpp / Filter.h
├── GrayscaleImage.cpp / GrayscaleImage.h
├── SecretImage.cpp / SecretImage.h
├── main.cpp
├── Makefile
└── README.md


## Usage  
Example commands:
```bash
./clearvision mean input.png 3
./clearvision gauss input.png 3 1.0
./clearvision unsharp input.png 3 0.5
./clearvision add img1.png img2.png
./clearvision sub img1.png img2.png
./clearvision equals img1.png img2.png
./clearvision enc image.png "Kurt sürüsü harekete geçti"
./clearvision dec image.png 28

g++ -g -std=c++11 -o clearvision main.cpp SecretImage.cpp GrayscaleImage.cpp Filter.cpp Crypto.cpp
or
make


Author

Yusuf Demiray

Hacettepe University — Computer Engineering
