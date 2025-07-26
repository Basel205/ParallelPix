#include "effects.hpp"
#include <vector>
#include <algorithm>

void ImageProcessor::pencil_sketch(bool parallel) {
    std::vector<unsigned char> grayscale(width * height);
    #pragma omp parallel for schedule(static) if(parallel)
    for (int i = 0; i < width * height; i++) {
        grayscale[i] = static_cast<unsigned char>(
            0.299 * pixels[i].r + 0.587 * pixels[i].g + 0.114 * pixels[i].b);
    }

    std::vector<unsigned char> inverted(width * height);
    #pragma omp parallel for schedule(static) if(parallel)
    for (int i = 0; i < width * height; i++) {
        inverted[i] = 255 - grayscale[i];
    }

    std::vector<Pixel> blurred(width * height);
    for (int i = 0; i < width * height; i++) {
        blurred[i] = {inverted[i], inverted[i], inverted[i]};
    }

    std::vector<Pixel> temp(width * height);
    gaussian_blur_horizontal(blurred, temp, 5, parallel);
    gaussian_blur_vertical(temp, blurred, 5, parallel);

    #pragma omp parallel for schedule(static) if(parallel)
    for (int i = 0; i < width * height; i++) {
        int blend = (grayscale[i] << 8) / (256 - blurred[i].r + 1);
        pixels[i] = {
            static_cast<unsigned char>(std::min(blend, 255)),
            static_cast<unsigned char>(std::min(blend, 255)),
            static_cast<unsigned char>(std::min(blend, 255))
        };
    }
}
