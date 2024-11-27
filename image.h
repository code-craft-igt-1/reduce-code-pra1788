#pragma once

#include <cstdint>
#include <vector>
#include <functional>

class Image {
 public:
    int m_rows, m_columns;
    std::vector<uint8_t> pixels;  // A vector of (grayscale) pixels

    Image(int rows, int columns) : m_rows(rows), m_columns(columns), pixels(rows * columns) {}

    // Method to process each pixel in the image
    void Image::processPixels(const std::function<void(int, int, uint8_t&)>& processor);
};
