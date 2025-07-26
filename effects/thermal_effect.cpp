#include "effects.hpp"

void ImageProcessor::thermal_effect(bool parallel) {
    #pragma omp parallel for schedule(static) if(parallel && width*height > 500000)
    for (int i = 0; i < width * height; i++) {
        int intensity = (pixels[i].r + pixels[i].g + pixels[i].b) / 3;

        if (intensity < 64) {
            pixels[i] = {0, 0, static_cast<unsigned char>(intensity * 4)};
        } 
        else if (intensity < 128) {
            pixels[i] = {
                static_cast<unsigned char>((intensity - 64) * 4),
                0,
                static_cast<unsigned char>(255 - (intensity - 64) * 4)
            };
        }
        else if (intensity < 192) {
            pixels[i] = {
                static_cast<unsigned char>(255),
                static_cast<unsigned char>((intensity - 128) * 4),
                static_cast<unsigned char>(0)
            };
        }
        else {
            pixels[i] = {
                static_cast<unsigned char>(255),
                static_cast<unsigned char>(255),
                static_cast<unsigned char>((intensity - 192) * 4)
            };
        }
    }
}
