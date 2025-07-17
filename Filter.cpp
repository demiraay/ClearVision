#include "Filter.h"
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
#include <numeric>
#include <math.h>
#include <ostream>



// Mean Filter
void Filter::apply_mean_filter(GrayscaleImage& image, int kernelSize) {
    // TODO: Your code goes here.
    // 1. Copy the original image for reference.
    // 2. For each pixel, calculate the mean value of its neighbors using a kernel.
    // 3. Update each pixel with the computed mean.

    GrayscaleImage  new_image(image.get_width(), image.get_height());


    int height = image.get_height();
    int width = image.get_width();
    int halfSize = kernelSize / 2;




    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int sum = 0;


            for (int ki = -halfSize; ki <= halfSize; ++ki) {
                for (int kj = -halfSize; kj <= halfSize; ++kj) {
                    int ni = i + ki;
                    int nj = j + kj;


                    if (ni >= 0 && ni < height && nj >= 0 && nj < width) {
                        sum += image.get_pixel(ni, nj);

                    }
                }
            }


            int meanValue = sum / (kernelSize*kernelSize);
            new_image.set_pixel(i, j, meanValue);
        }
    }

    for (int i = 0; i < height; ++i) {

        for (int j = 0; j < width; ++j) {
            image.set_pixel(i, j, new_image.get_pixel(i, j));


        }
    }


}

// Gaussian Smoothing Filter
void Filter::apply_gaussian_smoothing(GrayscaleImage& image, int kernelSize, double sigma) {
    // TODO: Your code goes here.
    // 1. Create a Gaussian kernel based on the given sigma value.
    // 2. Normalize the kernel to ensure it sums to 1.
    // 3. For each pixel, compute the weighted sum using the kernel.
    // 4. Update the pixel values with the smoothed results.

    GrayscaleImage new_image(image.get_width(), image.get_height());
    int width = image.get_width();
    int height = image.get_height();
    int halfSize = kernelSize / 2;
    double sum_for_kernel = 0.0;



    double** kernel = new double*[kernelSize];
    for (int i = 0; i < kernelSize; ++i) {
        kernel[i] = new double[kernelSize];
    }

    for (int i = -halfSize; i <= halfSize; ++i) {
        for (int j = -halfSize; j <= halfSize; ++j) {
            kernel[i + halfSize][j + halfSize] = (1 / (2 * M_PI * sigma * sigma)) *
                                                  exp(-(i * i + j * j) / (2 * sigma * sigma));
            sum_for_kernel += kernel[i + halfSize][j + halfSize];
        }
    }


    for (int i = 0; i < kernelSize; ++i) {

        for (int j = 0; j < kernelSize; ++j) {
            kernel[i][j] /= sum_for_kernel;

        }
    }

    for (int i = 0; i < height; ++i) {

        for (int j = 0; j < width; ++j) {
            double weightedSum = 0.0;


            for (int ki = -halfSize; ki <= halfSize; ++ki) {
                for (int kj = -halfSize; kj <= halfSize; ++kj) {
                    int ni = i + ki;
                    int nj = j + kj;


                    if (ni >= 0 && ni < height && nj >= 0 && nj < width) {
                        weightedSum += image.get_pixel(ni, nj) * kernel[ki + halfSize][kj + halfSize];

                    }
                }
            }


            new_image.set_pixel(i, j, static_cast<int>(weightedSum));

        }
    }

    for (int i = 0; i < height; ++i) {

        for (int j = 0; j < width; ++j) {
            image.set_pixel(i, j, new_image.get_pixel(i, j));

        }
    }

    for (int i = 0; i < kernelSize; ++i) {
        delete[] kernel[i];
    }
    delete[] kernel;





}

// Unsharp Masking Filter
void Filter::apply_unsharp_mask(GrayscaleImage& image, int kernelSize, double amount) {
    // TODO: Your code goes here.
    // 1. Blur the image using Gaussian smoothing, use the default sigma given in the header.
    // 2. For each pixel, apply the unsharp mask formula: original + amount * (original - blurred).
    // 3. Clip values to ensure they are within a valid range [0-255].

    GrayscaleImage smoothed_image (image);
    apply_gaussian_smoothing(smoothed_image, kernelSize, 1);

    for (int i = 0; i < image.get_height(); ++i) {
        for (int j = 0; j < image.get_width(); ++j) {
              image.set_pixel(i, j,image.get_pixel(i, j) + amount * (image.get_pixel(i, j) - smoothed_image.get_pixel(i, j))) ;
            if (image.get_pixel(i, j) > 255) {
                image.set_pixel(i, j, 255);
            }
            else if (image.get_pixel(i, j) < 0) {
                image.set_pixel(i, j, 0);
            }
        }
    }


}
