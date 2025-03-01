# ImageFilterApp

A desktop application for applying various image filters without relying on external image processing libraries. This application is built using Qt and implements custom filters that operate directly on image pixels.

## Features

- Simple and intuitive user interface
- Load images in popular formats (PNG, JPEG, BMP, GIF)
- Apply various filters to images
- Save processed images
- Reset to original image

## Implemented Filters

The application includes the following filters:

### 1. Inversion Filter
Inverts each color channel, creating a negative of the original image. This filter swaps light and dark areas and converts each color to its complementary color.

### 2. Brightness Correction
Adjusts the brightness of the image by adding a constant value to each color channel. Positive values make the image brighter, while negative values make it darker.

### 3. Contrast Enhancement
Enhances or reduces the contrast of the image by stretching or compressing the range of color values relative to a midpoint. Higher contrast values make the difference between dark and light areas more pronounced.

### 4. Gamma Correction
Applies a nonlinear adjustment to the image's luminance. This is particularly useful for:
- Correcting for the nonlinear response of displays
- Enhancing details in shadows (gamma < 1)
- Enhancing details in highlights (gamma > 1)

## How to Use

1. **Launch the application**
2. **Load an image** by clicking the "Load" button
3. **Select a filter** from the dropdown menu
4. **Apply the filter** by clicking the "Apply" button
5. **Reset to original** if desired using the "Reset" button
6. **Save the processed image** using the "Save" button

## Technical Details

### Filter Implementation

All filters are implemented from scratch without external image processing libraries. They operate directly on pixels, manipulating RGB values according to the specific algorithm of each filter.

Optimizations include:
- Lookup tables for gamma correction to improve performance
- Input validation and range clamping to ensure valid pixel values
- Parameter constants defined in the header files for easy customization

### Dependencies

- Qt Framework for the GUI and basic image I/O operations

### Project Structure

- **gui/**: Contains the UI implementation files
- **filters/**: Contains the filter implementations

## Future Enhancements

Possible future enhancements could include:
- User-adjustable filter parameters via sliders
- Histogram visualization
- Batch processing
- Additional filters (blur, sharpen, edge detection, etc.)
- Filter combinations

## License

This project is for educational purposes. 
