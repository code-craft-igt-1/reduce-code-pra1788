#include <gtest/gtest.h>
#include <memory>
#include <vector>
#include "../brightener.h"

namespace brighteningtest {

class BrighteningTest : public ::testing::Test {
 protected:
    std::shared_ptr<Image> image;
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// this helped to reduce duplication
std::shared_ptr<Image> InitializeImage(const std::vector<uint8_t>& pixelValues, int rows, int columns) {
    auto newImage = std::make_shared<Image>(rows, columns);
    for (int i = 0; i < pixelValues.size(); ++i) {
        newImage->pixels[i] = pixelValues[i];
    }
    return newImage;
}

TEST_F(BrighteningTest, BrightensWholeImage) {
    image = InitializeImage({45, 55, 65, 254}, 2, 2);
    ImageBrightener brightener(image);
    int attenuatedCount = brightener.BrightenWholeImage();

    EXPECT_EQ(attenuatedCount, 1);
    EXPECT_EQ(image->pixels[2], 90);
}

TEST_F(BrighteningTest, BrightensWithAnotherImage) {
    image = InitializeImage({45, 55, 65, 75}, 2, 2);
    ImageBrightener brightener(image);

    auto brighteningImage = InitializeImage({0, 25, 0, 25}, 2, 2);
    int attenuatedCount = 0;
    bool succeeded = brightener.AddBrighteningImage(brighteningImage, &attenuatedCount);

    EXPECT_TRUE(succeeded);
    EXPECT_EQ(image->pixels[0], 45);
    EXPECT_EQ(image->pixels[1], 80);
    EXPECT_EQ(attenuatedCount, 0);
}

}  // namespace brighteningtest end
