// effects/image_processor.cpp
// effects/image_processor.cpp
#include "effects.hpp"

// Add implementation definitions
#define STB_IMAGE_IMPLEMENTATION
#include "../libs/stb/stb_image.h" 
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../libs/stb/stb_image_write.h"  

#include <iostream>

bool ImageProcessor::load(const char* filename) {
    int channels;
    unsigned char* data = stbi_load(filename, &width, &height, &channels, 3);
    if (!data) {
        std::cerr << "Error loading image: " << stbi_failure_reason() << std::endl;
        return false;
    }

    pixels.resize(width * height);
    for (int i = 0; i < width * height; i++) {
        pixels[i] = {data[3*i], data[3*i+1], data[3*i+2]};
    }

    stbi_image_free(data);
    return true;
}

bool ImageProcessor::save(const char* filename) {
    std::vector<unsigned char> data(pixels.size() * 3);
    for (size_t i = 0; i < pixels.size(); i++) {
        data[3*i] = pixels[i].r;
        data[3*i+1] = pixels[i].g;
        data[3*i+2] = pixels[i].b;
    }
    return stbi_write_jpg(filename, width, height, 3, data.data(), 95);
}

void ImageProcessor::apply_filter(const std::string& filter, int param, bool parallel) {
    if (filter == "blur") {
        gaussian_blur(param, parallel);
    }
    else if (filter == "anime") {
        anime_style(parallel);
    }
    else if (filter == "oil") {
        oil_painting(param, 8, parallel);
    }
    else if (filter == "pencil") {
        pencil_sketch(parallel);
    }
    else if (filter == "thermal") {
        thermal_effect(parallel);
    }
}
