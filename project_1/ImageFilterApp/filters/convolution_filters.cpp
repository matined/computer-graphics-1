#include "convolution_filters.h"
#include <algorithm>
#include <cmath>
#include <vector>

namespace ConvolutionFilters {

    void applyConvolution(QImage &image, const std::array<std::array<float, KERNEL_SIZE>, KERNEL_SIZE> &kernel) {
        // Create a copy of the original image to read from while we modify the original
        QImage originalImage = image.copy();
        
        // Make sure we're working with a format that has correct RGB values
        if (originalImage.format() == QImage::Format_ARGB32_Premultiplied) {
            originalImage = originalImage.convertToFormat(QImage::Format_ARGB32);
            image = image.convertToFormat(QImage::Format_ARGB32);
        }
        
        // Process each pixel in the image
        for (int y = 0; y < image.height(); ++y) {
            for (int x = 0; x < image.width(); ++x) {
                float sumRed = 0.0f;
                float sumGreen = 0.0f;
                float sumBlue = 0.0f;
                
                // Apply the kernel to the neighborhood of the current pixel
                for (int ky = -KERNEL_RADIUS; ky <= KERNEL_RADIUS; ++ky) {
                    for (int kx = -KERNEL_RADIUS; kx <= KERNEL_RADIUS; ++kx) {
                        // Calculate sample position with bounds checking (clamping to edges)
                        int sampleX = std::max(0, std::min(originalImage.width() - 1, x + kx));
                        int sampleY = std::max(0, std::min(originalImage.height() - 1, y + ky));
                        
                        // Get the pixel value from the original image
                        QRgb pixel = originalImage.pixel(sampleX, sampleY);
                        
                        // Get the kernel value (kernel is centered, so add KERNEL_RADIUS to indices)
                        float kernelValue = kernel[ky + KERNEL_RADIUS][kx + KERNEL_RADIUS];
                        
                        // Accumulate weighted color components
                        sumRed += qRed(pixel) * kernelValue;
                        sumGreen += qGreen(pixel) * kernelValue;
                        sumBlue += qBlue(pixel) * kernelValue;
                    }
                }
                
                // Clamp values to valid range [0, 255]
                int red = std::max(0, std::min(255, static_cast<int>(std::round(sumRed))));
                int green = std::max(0, std::min(255, static_cast<int>(std::round(sumGreen))));
                int blue = std::max(0, std::min(255, static_cast<int>(std::round(sumBlue))));
                
                // Preserve the original alpha value
                int alpha = qAlpha(originalImage.pixel(x, y));
                
                // Set the new pixel value in the output image
                image.setPixel(x, y, qRgba(red, green, blue, alpha));
            }
        }
    }
    
    void applyBlurFilter(QImage &image) {
        // Apply the blur kernel to the image
        applyConvolution(image, BLUR_KERNEL);
    }
    
    void applyGaussianBlurFilter(QImage &image) {
        // Apply the Gaussian blur kernel to the image
        applyConvolution(image, GAUSSIAN_KERNEL);
    }
    
    void applySharpenFilter(QImage &image) {
        // Apply the sharpen kernel to the image
        applyConvolution(image, SHARPEN_KERNEL);
    }
    
    void applyEdgeFilter(QImage &image) {
        // Apply the edge detection kernel to the image
        applyConvolution(image, EDGE_KERNEL);
    }
    
    void applyEmbossFilter(QImage &image) {
        // Apply the emboss kernel to the image
        applyConvolution(image, EMBOSS_KERNEL);
    }
    
    void applyMedianFilter(QImage &image, int kernelSize) {
        // Ensure kernel size is odd (for a centered filter)
        if (kernelSize % 2 == 0) {
            kernelSize++; // Make it odd if it's even
        }
        
        // Ensure minimum size of 3
        kernelSize = std::max(3, kernelSize);
        
        // Calculate the radius of the kernel
        int radius = kernelSize / 2;
        
        // Create a copy of the original image to read from while we modify the original
        QImage originalImage = image.copy();
        
        // Make sure we're working with a format that has correct RGB values
        if (originalImage.format() == QImage::Format_ARGB32_Premultiplied) {
            originalImage = originalImage.convertToFormat(QImage::Format_ARGB32);
            image = image.convertToFormat(QImage::Format_ARGB32);
        }
        
        // Process each pixel in the image
        for (int y = 0; y < image.height(); ++y) {
            for (int x = 0; x < image.width(); ++x) {
                // Vectors to store neighborhood values for each channel
                std::vector<int> redValues;
                std::vector<int> greenValues;
                std::vector<int> blueValues;
                
                // Reserve space to avoid reallocations
                redValues.reserve(kernelSize * kernelSize);
                greenValues.reserve(kernelSize * kernelSize);
                blueValues.reserve(kernelSize * kernelSize);
                
                // Collect pixel values in the neighborhood
                for (int ky = -radius; ky <= radius; ++ky) {
                    for (int kx = -radius; kx <= radius; ++kx) {
                        // Calculate sample position with bounds checking (clamping to edges)
                        int sampleX = std::max(0, std::min(originalImage.width() - 1, x + kx));
                        int sampleY = std::max(0, std::min(originalImage.height() - 1, y + ky));
                        
                        // Get the pixel value from the original image
                        QRgb pixel = originalImage.pixel(sampleX, sampleY);
                        
                        // Add color components to the vectors
                        redValues.push_back(qRed(pixel));
                        greenValues.push_back(qGreen(pixel));
                        blueValues.push_back(qBlue(pixel));
                    }
                }
                
                // Sort each channel's values to find median
                std::sort(redValues.begin(), redValues.end());
                std::sort(greenValues.begin(), greenValues.end());
                std::sort(blueValues.begin(), blueValues.end());
                
                // Calculate median index
                int medianIndex = redValues.size() / 2;
                
                // Get median values for each channel
                int medianRed = redValues[medianIndex];
                int medianGreen = greenValues[medianIndex];
                int medianBlue = blueValues[medianIndex];
                
                // Preserve the original alpha value
                int alpha = qAlpha(originalImage.pixel(x, y));
                
                // Set the new pixel value with median colors in the output image
                image.setPixel(x, y, qRgba(medianRed, medianGreen, medianBlue, alpha));
            }
        }
    }
}
