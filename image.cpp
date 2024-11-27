#include "./image.h"

void Image::processPixels(const std::function<void(int, int, uint8_t&)>& processor) {
    for (int x = 0; x < m_rows; ++x) {
        for (int y = 0; y < m_columns; ++y) {
            int pixelIndex = x * m_columns + y;
            processor(x, y, pixels[pixelIndex]);
        }
    }
}
