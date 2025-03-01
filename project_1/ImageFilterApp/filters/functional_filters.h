#ifndef FUNCTIONAL_FILTERS_H
#define FUNCTIONAL_FILTERS_H

#include <QImage>

namespace Filters {
    // Filter Parameters
    const int BRIGHTNESS_MIN = -255;
    const int BRIGHTNESS_MAX = 255;
    const int BRIGHTNESS_DEFAULT = 200;  // Default brightness adjustment value
    
    const double CONTRAST_MIN = 0.0;     // Minimum contrast factor (0 = gray image)
    const double CONTRAST_MAX = 3.0;     // Maximum contrast factor
    const double CONTRAST_DEFAULT = 1.5; // Default contrast enhancement value
    
    const double GAMMA_MIN = 0.1;        // Minimum gamma value
    const double GAMMA_MAX = 5.0;        // Maximum gamma value
    const double GAMMA_DEFAULT = 0.5;    // Default gamma value (0.5 = lighter image)
    
    // Apply inversion filter to an image
    void applyInversionFilter(QImage &image);
    
    // Apply brightness correction filter to an image
    // brightness: value between BRIGHTNESS_MIN and BRIGHTNESS_MAX
    // Positive values increase brightness, negative values decrease it
    void applyBrightnessFilter(QImage &image, int brightness = BRIGHTNESS_DEFAULT);
    
    // Apply contrast enhancement filter to an image
    // contrast: value between CONTRAST_MIN and CONTRAST_MAX
    // 1.0 = no change, >1.0 increases contrast, <1.0 decreases contrast
    void applyContrastFilter(QImage &image, double contrast = CONTRAST_DEFAULT);
    
    // Apply gamma correction filter to an image
    // gamma: value between GAMMA_MIN and GAMMA_MAX
    // <1.0 lightens the image, >1.0 darkens the image, 1.0 = no change
    void applyGammaFilter(QImage &image, double gamma = GAMMA_DEFAULT);
}

#endif // FUNCTIONAL_FILTERS_H
