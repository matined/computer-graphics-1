#include "functional_filters.h"

#include <algorithm>
#include <cmath>

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
}
