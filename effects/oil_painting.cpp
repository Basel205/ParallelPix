#include "effects.hpp"
#include <vector>
#include <algorithm>

void ImageProcessor::oil_painting(int radius, int levels, bool parallel) {
    std::vector<Pixel> result(width * height);

    #pragma omp parallel for schedule(dynamic, 8) if(parallel)
    for (int y = 0; y < height; y++) {
        // Local variables for each thread
        std::vector<int> intensityCount(levels, 0);
        std::vector<int> avgR(levels, 0);
        std::vector<int> avgG(levels, 0);
        std::vector<int> avgB(levels, 0);

        for (int x = 0; x < width; x++) {
            std::fill(intensityCount.begin(), intensityCount.end(), 0);
            std::fill(avgR.begin(), avgR.end(), 0);
            std::fill(avgG.begin(), avgG.end(), 0);
            std::fill(avgB.begin(), avgB.end(), 0);

            for (int dy = -radius; dy <= radius; dy++) {
                for (int dx = -radius; dx <= radius; dx++) {
                    int nx = std::clamp(x + dx, 0, width - 1);
                    int ny = std::clamp(y + dy, 0, height - 1);

                    Pixel p = pixels[ny * width + nx];
                    int intensity = (p.r + p.g + p.b) / 3;
                    int level = intensity * levels / 256;

                    intensityCount[level]++;
                    avgR[level] += p.r;
                    avgG[level] += p.g;
                    avgB[level] += p.b;
                }
            }

            int maxCount = 0;
            int maxLevel = 0;
            for (int i = 0; i < levels; i++) {
                if (intensityCount[i] > maxCount) {
                    maxCount = intensityCount[i];
                    maxLevel = i;
                }
            }

            result[y * width + x] = {
                static_cast<unsigned char>(avgR[maxLevel] / maxCount),
                static_cast<unsigned char>(avgG[maxLevel] / maxCount),
                static_cast<unsigned char>(avgB[maxLevel] / maxCount)
            };
        }
    }

    pixels = result;
}
