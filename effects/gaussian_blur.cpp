#include "effects.hpp"
#include <vector>

void ImageProcessor::gaussian_blur_horizontal(std::vector<Pixel>& src, std::vector<Pixel>& dst, int radius, bool parallel) {
    std::vector<float> kernel(radius * 2 + 1);
    float sigma = radius / 2.0f;
    float sum = 0.0f;
    
    for(int i = -radius; i <= radius; ++i) {
        kernel[i + radius] = expf(-(i*i)/(2*sigma*sigma));
        sum += kernel[i + radius];
    }
    for(float& k : kernel) k /= sum;

    #pragma omp parallel for schedule(dynamic, 16) if(parallel)
    for(int y = 0; y < height; ++y) {
        for(int x = 0; x < width; ++x) {
            float r = 0, g = 0, b = 0;
            for(int i = -radius; i <= radius; ++i) {
                int xi = std::clamp(x+i, 0, width-1);
                const Pixel& p = src[y*width + xi];
                float weight = kernel[i+radius];
                r += p.r * weight;
                g += p.g * weight;
                b += p.b * weight;
            }
            dst[y*width+x] = {
                static_cast<unsigned char>(r),
                static_cast<unsigned char>(g),
                static_cast<unsigned char>(b)
            };
        }
    }
}

void ImageProcessor::gaussian_blur_vertical(std::vector<Pixel>& src, std::vector<Pixel>& dst, int radius, bool parallel) {
    std::vector<float> kernel(radius * 2 + 1);
    float sigma = radius / 2.0f;
    float sum = 0.0f;
    
    for(int i = -radius; i <= radius; ++i) {
        kernel[i + radius] = expf(-(i*i)/(2*sigma*sigma));
        sum += kernel[i + radius];
    }
    for(float& k : kernel) k /= sum;

    #pragma omp parallel for schedule(dynamic, 16) if(parallel)
    for(int x = 0; x < width; ++x) {
        for(int y = 0; y < height; ++y) {
            float r = 0, g = 0, b = 0;
            for(int i = -radius; i <= radius; ++i) {
                int yi = std::clamp(y+i, 0, height-1);
                const Pixel& p = src[yi*width + x];
                float weight = kernel[i+radius];
                r += p.r * weight;
                g += p.g * weight;
                b += p.b * weight;
            }
            dst[y*width+x] = {
                static_cast<unsigned char>(r),
                static_cast<unsigned char>(g),
                static_cast<unsigned char>(b)
            };
        }
    }
}

void ImageProcessor::gaussian_blur(int radius, bool parallel) {
    std::vector<Pixel> temp(pixels.size());
    std::vector<Pixel> result(pixels.size());
    
    gaussian_blur_horizontal(pixels, temp, radius, parallel);
    gaussian_blur_vertical(temp, result, radius, parallel);
    
    pixels = result;
}
