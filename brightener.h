#pragma once

#include <memory>
#include "./image.h"

class ImageBrightener {
 private:
    std::shared_ptr<Image> m_inputImage;

 public:
    explicit ImageBrightener(std::shared_ptr<Image> inputImage);

    // Brighten the entire image
    int BrightenWholeImage();

    // Add the pixel values of another image to the current image
    bool AddBrighteningImage(std::shared_ptr<Image> imageToAdd, int* attenuatedCount);
    // Helper function
    bool AreImagesCompatible(std::shared_ptr<Image> imageToAdd);
};
