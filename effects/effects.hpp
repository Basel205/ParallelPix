#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <omp.h>

struct Pixel {
    unsigned char r, g, b;
};

class ImageProcessor {
public:
    std::vector<Pixel> pixels;
    int width, height;
    
    // Gaussian blur helpers
    void gaussian_blur_horizontal(std::vector<Pixel>& src, std::vector<Pixel>& dst, int radius, bool parallel);
    void gaussian_blur_vertical(std::vector<Pixel>& src, std::vector<Pixel>& dst, int radius, bool parallel);
    
public:
    bool load(const char* filename);
    bool save(const char* filename);
    void apply_filter(const std::string& filter, int param, bool parallel);
    
    // Effects
    void gaussian_blur(int radius, bool parallel);
    void anime_style(bool parallel);
    void oil_painting(int radius, int levels, bool parallel);
    void pencil_sketch(bool parallel);
    void thermal_effect(bool parallel);
};
