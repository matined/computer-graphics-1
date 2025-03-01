#ifndef CONVOLUTION_FILTERS_H
#define CONVOLUTION_FILTERS_H

#include <QImage>
#include <array>

namespace ConvolutionFilters {
    // Constants for kernel sizes
    constexpr int KERNEL_SIZE = 3;
    constexpr int KERNEL_RADIUS = KERNEL_SIZE / 2;
    
    // Blur filter kernel (Box blur - equal weights)
    constexpr std::array<std::array<float, KERNEL_SIZE>, KERNEL_SIZE> BLUR_KERNEL = {{
        {{1.0f/9.0f, 1.0f/9.0f, 1.0f/9.0f}},
        {{1.0f/9.0f, 1.0f/9.0f, 1.0f/9.0f}},
        {{1.0f/9.0f, 1.0f/9.0f, 1.0f/9.0f}}
    }};
    
    // Gaussian blur filter kernel (weighted blur - more weight in center)
    constexpr std::array<std::array<float, KERNEL_SIZE>, KERNEL_SIZE> GAUSSIAN_KERNEL = {{
        {{1.0f/16.0f, 2.0f/16.0f, 1.0f/16.0f}},
        {{2.0f/16.0f, 4.0f/16.0f, 2.0f/16.0f}},
        {{1.0f/16.0f, 2.0f/16.0f, 1.0f/16.0f}}
    }};
    
    // Sharpen filter kernel (enhances edges and details)
    constexpr std::array<std::array<float, KERNEL_SIZE>, KERNEL_SIZE> SHARPEN_KERNEL = {{
        {{ 0.0f, -1.0f,  0.0f}},
        {{-1.0f,  5.0f, -1.0f}},
        {{ 0.0f, -1.0f,  0.0f}}
    }};
    
    // Vertical edge detection kernel (Sobel operator for vertical edges)
    constexpr std::array<std::array<float, KERNEL_SIZE>, KERNEL_SIZE> EDGE_KERNEL = {{
        {{-1.0f, 0.0f, 1.0f}},
        {{-2.0f, 0.0f, 2.0f}},
        {{-1.0f, 0.0f, 1.0f}}
    }};

    // Emboss filter kernel (creates a 3D-like effect)
    constexpr std::array<std::array<float, KERNEL_SIZE>, KERNEL_SIZE> EMBOSS_KERNEL = {{
        {{-2.0f, -1.0f, 0.0f}},
        {{-1.0f,  1.0f, 1.0f}},
        {{ 0.0f,  1.0f, 2.0f}}
    }};

    // Apply a generic convolution with the specified kernel to an image
    void applyConvolution(QImage &image, const std::array<std::array<float, KERNEL_SIZE>, KERNEL_SIZE> &kernel);
    
    // Apply blur filter using the BLUR_KERNEL
    void applyBlurFilter(QImage &image);
    
    // Apply Gaussian blur filter using the GAUSSIAN_KERNEL
    void applyGaussianBlurFilter(QImage &image);
    
    // Apply sharpen filter using the SHARPEN_KERNEL
    void applySharpenFilter(QImage &image);
    
    // Apply vertical edge detection filter using the EDGE_KERNEL
    void applyEdgeFilter(QImage &image);
    
    // Apply emboss filter using the EMBOSS_KERNEL
    void applyEmbossFilter(QImage &image);
}

#endif // CONVOLUTION_FILTERS_H
