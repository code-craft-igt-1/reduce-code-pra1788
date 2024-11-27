#include "./brightener.h"

// Constructor
ImageBrightener::ImageBrightener(std::shared_ptr<Image> inputImage) : m_inputImage(inputImage) {}

// Brightens the entire image by adding a constant to each pixel
int ImageBrightener::BrightenWholeImage() {
    int attenuatedPixelCount = 0;

    // Lambda to brighten pixels and count those that are saturated
    std::function<void(int, int, uint8_t&)> brightenLambda =
    [this, &attenuatedPixelCount](int x, int y, uint8_t& pixel) {
        if (pixel > (255 - 25)) {
            ++attenuatedPixelCount;
            pixel = 255;  // Set pixel to max value if it's too bright
        } else {
            pixel += 25;  // Otherwise, add a constant to brighten it
        }
    };

    m_inputImage->processPixels(brightenLambda);
    return attenuatedPixelCount;
}

// Adds pixel values from another image, ensuring the result doesn't exceed 255
bool ImageBrightener::AddBrighteningImage(std::shared_ptr<Image> imageToAdd, int* attenuatedCount) {
    // Early return if images are incompatible in size
    if (!AreImagesCompatible(imageToAdd)) {
        return false;
    }

    *attenuatedCount = 0;  // Initialize attenuated count

    // Lambda to add pixel brightness from another image
    auto addBrightnessLambda = [this, imageToAdd, attenuatedCount](int x, int y, uint8_t& pixel) {
        int pixelIndex = x * m_inputImage->m_columns + y;
        uint8_t newPixelValue = pixel + imageToAdd->pixels[pixelIndex];
        if (newPixelValue > 255) {
            pixel = 255;
            (*attenuatedCount)++;  // Increment attenuated count if pixel value is capped
        } else {
            pixel = newPixelValue;  // Otherwise, just update pixel value
        }
    };

    m_inputImage->processPixels(addBrightnessLambda);
    return true;
}

// Helper function to check if the images have the same dimensions this helped to reduce CCN < 3
bool ImageBrightener::AreImagesCompatible(std::shared_ptr<Image> imageToAdd) {
    return imageToAdd->m_rows == m_inputImage->m_rows && imageToAdd->m_columns == m_inputImage->m_columns;
}
