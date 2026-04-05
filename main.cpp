#include <iostream>
#include <cstdio>
#include "Image.h"

int main() {
    using namespace NkMath;
    printf("=== TP6: Image Processing (Adaptive Threshold) ===\n\n");

    NkImage img(256, 256);
    // Create a gradient pattern
    for (int y = 0; y < 256; y++) {
        for (int x = 0; x < 256; x++) {
            img.SetPixel(x, y, (uint8_t)x, (uint8_t)y, 128);
        }
    }
    // Add a dark circle
    for (int y = 50; y < 150; y++) {
        for (int x = 50; x < 150; x++) {
            if (std::sqrt((x-100)*(x-100) + (y-100)*(y-100)) < 40) img.SetPixel(x, y, 20, 20, 20);
        }
    }
    img.SavePPM("test_input.ppm");
    printf("1. Image de test generee (test_input.ppm)\n");

    NkImage binarized = AdaptiveThreshold(img, 31, 5);
    binarized.SavePPM("test_binarized.ppm");
    printf("2. Image binarisee via Adaptive Threshold generee (test_binarized.ppm)\n");

    return 0;
}
