#include "functional_filters.h"

#include <algorithm>
#include <cmath>
#include <random>

namespace Filters {
    void applyInversionFilter(QImage &image) {
        // Process each pixel in the image
        for (int y = 0; y < image.height(); ++y) {
            for (int x = 0; x < image.width(); ++x) {
                QRgb pixel = image.pixel(x, y);
                
                // Invert each color component (R, G, B)
                int invertedRed = 255 - qRed(pixel);
                int invertedGreen = 255 - qGreen(pixel);
                int invertedBlue = 255 - qBlue(pixel);
                
                // Keep the original alpha value
                int alpha = qAlpha(pixel);
                
                // Set the inverted pixel value
                image.setPixel(x, y, qRgba(invertedRed, invertedGreen, invertedBlue, alpha));
            }
        }
    }
    
    void applyBrightnessFilter(QImage &image, int brightness) {
        // Ensure brightness is within the valid range
        brightness = std::max(BRIGHTNESS_MIN, std::min(brightness, BRIGHTNESS_MAX));
        
        // Process each pixel in the image
        for (int y = 0; y < image.height(); ++y) {
            for (int x = 0; x < image.width(); ++x) {
                QRgb pixel = image.pixel(x, y);
                
                // Extract color components
                int red = qRed(pixel);
                int green = qGreen(pixel);
                int blue = qBlue(pixel);
                int alpha = qAlpha(pixel);
                
                // Apply brightness adjustment with clamping to valid range [0, 255]
                red = std::max(0, std::min(255, red + brightness));
                green = std::max(0, std::min(255, green + brightness));
                blue = std::max(0, std::min(255, blue + brightness));
                
                // Set the adjusted pixel
                image.setPixel(x, y, qRgba(red, green, blue, alpha));
            }
        }
    }
    
    void applyContrastFilter(QImage &image, double contrast) {
        // Ensure contrast is within the valid range
        contrast = std::max(CONTRAST_MIN, std::min(contrast, CONTRAST_MAX));
        
        // Define the midpoint for contrast adjustment (typically 128 for 8-bit images)
        const int midpoint = 128;
        
        // Process each pixel in the image
        for (int y = 0; y < image.height(); ++y) {
            for (int x = 0; x < image.width(); ++x) {
                QRgb pixel = image.pixel(x, y);
                
                // Extract color components
                int red = qRed(pixel);
                int green = qGreen(pixel);
                int blue = qBlue(pixel);
                int alpha = qAlpha(pixel);
                
                // Apply contrast adjustment formula: newValue = (oldValue - midpoint) * contrast + midpoint
                red = std::max(0, std::min(255, static_cast<int>((red - midpoint) * contrast + midpoint)));
                green = std::max(0, std::min(255, static_cast<int>((green - midpoint) * contrast + midpoint)));
                blue = std::max(0, std::min(255, static_cast<int>((blue - midpoint) * contrast + midpoint)));
                
                // Set the adjusted pixel
                image.setPixel(x, y, qRgba(red, green, blue, alpha));
            }
        }
    }
    
    void applyGammaFilter(QImage &image, double gamma) {
        
        // Ensure gamma is within the valid range
        gamma = std::max(GAMMA_MIN, std::min(gamma, GAMMA_MAX));
        
        // Create a gamma correction lookup table for faster processing
        // This avoids recalculating the power function for every pixel
        int gammaLUT[256];
        for (int i = 0; i < 256; ++i) {
            // Normalize the value, apply gamma correction, then scale back
            double normalized = i / 255.0;
            double corrected = std::pow(normalized, 1.0 / gamma);
            gammaLUT[i] = static_cast<int>(std::round(corrected * 255.0));
            
            // Ensure values stay in valid range
            gammaLUT[i] = std::max(0, std::min(255, gammaLUT[i]));
        }
        
        // Process each pixel in the image
        for (int y = 0; y < image.height(); ++y) {
            for (int x = 0; x < image.width(); ++x) {
                QRgb pixel = image.pixel(x, y);
                
                // Extract color components
                int red = qRed(pixel);
                int green = qGreen(pixel);
                int blue = qBlue(pixel);
                int alpha = qAlpha(pixel);
                
                // Apply gamma correction using lookup table
                red = gammaLUT[red];
                green = gammaLUT[green];
                blue = gammaLUT[blue];
                
                // Set the adjusted pixel
                image.setPixel(x, y, qRgba(red, green, blue, alpha));
            }
        }
    }
    
    void applyRandomDitheringFilter(QImage &image, int redColors, int greenColors, int blueColors) {
        // Clamp the number of colors to valid range (2-256)
        redColors = std::max(2, std::min(256, redColors));
        greenColors = std::max(2, std::min(256, greenColors));
        blueColors = std::max(2, std::min(256, blueColors));
        
        // Calculate the step size for each color channel
        int redStep = 256 / (redColors - 1);
        int greenStep = 256 / (greenColors - 1);
        int blueStep = 256 / (blueColors - 1);
        
        // Random number generator
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dist(0.0f, 1.0f);
        
        // Process each pixel in the image
        for (int y = 0; y < image.height(); ++y) {
            for (int x = 0; x < image.width(); ++x) {
                QRgb pixel = image.pixel(x, y);
                
                // Extract color components
                int red = qRed(pixel);
                int green = qGreen(pixel);
                int blue = qBlue(pixel);
                int alpha = qAlpha(pixel);
                
                // Add random noise to each channel before quantizing
                float redNoise = dist(gen) * redStep;
                float greenNoise = dist(gen) * greenStep;
                float blueNoise = dist(gen) * blueStep;
                
                // Quantize with randomization
                int quantizedRed = ((red + redNoise) / redStep) * redStep;
                int quantizedGreen = ((green + greenNoise) / greenStep) * greenStep;
                int quantizedBlue = ((blue + blueNoise) / blueStep) * blueStep;
                
                // Clamp values to valid range [0, 255]
                quantizedRed = std::max(0, std::min(255, quantizedRed));
                quantizedGreen = std::max(0, std::min(255, quantizedGreen));
                quantizedBlue = std::max(0, std::min(255, quantizedBlue));
                
                // Set the dithered pixel
                image.setPixel(x, y, qRgba(quantizedRed, quantizedGreen, quantizedBlue, alpha));
            }
        }
    }
}
