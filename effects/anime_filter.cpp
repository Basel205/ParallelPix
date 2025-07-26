#include "effects.hpp"

void ImageProcessor::anime_style(bool parallel) {
    gaussian_blur(2, parallel);
    
    std::vector<unsigned char> edges(width * height, 0);
    #pragma omp parallel for schedule(dynamic, 16) if(parallel)
    for(int y = 1; y < height-1; y++) {
        for(int x = 1; x < width-1; x++) {
            int gx = (-pixels[(y-1)*width + x-1].r + pixels[(y-1)*width + x+1].r) +
                     (-2*pixels[y*width + x-1].r + 2*pixels[y*width + x+1].r) +
                     (-pixels[(y+1)*width + x-1].r + pixels[(y+1)*width + x+1].r);
            
            int gy = (-pixels[(y-1)*width + x-1].r + pixels[(y+1)*width + x-1].r) +
                     (-2*pixels[(y-1)*width + x].r + 2*pixels[(y+1)*width + x].r) +
                     (-pixels[(y-1)*width + x+1].r + pixels[(y+1)*width + x+1].r);
            
            edges[y*width + x] = (sqrt(gx*gx + gy*gy) > 30) ? 255 : 0;
        }
    }
    
    const int levels = 8;
    #pragma omp parallel for schedule(static) if(parallel)
    for(int i = 0; i < width*height; i++) {
        if(edges[i]) {
            pixels[i] = {0, 0, 0};
        } else {
            pixels[i].r = (pixels[i].r / (256/levels)) * (256/levels);
            pixels[i].g = (pixels[i].g / (256/levels)) * (256/levels);
            pixels[i].b = (pixels[i].b / (256/levels)) * (256/levels);
        }
    }
}
