#pragma once
#include <vector>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <cstdint>
#include <string>

namespace NkMath {

    class NkImage {
    public:
        int w, h;
        std::vector<uint8_t> data;

        NkImage(int w, int h) : w(w), h(h), data(w * h * 4, 0) {}

        void SetPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
            if (x >= 0 && x < w && y >= 0 && y < h) {
                int idx = (y * w + x) * 4;
                data[idx] = r; data[idx + 1] = g; data[idx + 2] = b; data[idx + 3] = a;
            }
        }

        uint8_t* At(int x, int y) { return &data[(y * w + x) * 4]; }

        std::vector<uint8_t> ToGrayscale() const {
            std::vector<uint8_t> gray(w * h);
            for (int i = 0; i < w * h; i++) {
                gray[i] = (uint8_t)(0.299f * data[i * 4] + 0.587f * data[i * 4 + 1] + 0.114f * data[i * 4 + 2]);
            }
            return gray;
        }

        void SavePPM(const std::string& path) const {
            std::ofstream f(path, std::ios::binary);
            if(!f) return;
            f << "P6\n" << w << " " << h << "\n255\n";
            for (int i = 0; i < w * h; i++) f.write((char*)&data[i * 4], 3);
        }
    };

    class IntegralImage {
        int w, h;
        std::vector<long long> table;
    public:
        IntegralImage(const std::vector<uint8_t>& gray, int w, int h) : w(w), h(h), table(w * h) {
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    long long val = gray[y * w + x];
                    if (x > 0) val += table[y * w + (x - 1)];
                    if (y > 0) val += table[(y - 1) * w + x];
                    if (x > 0 && y > 0) val -= table[(y - 1) * w + (x - 1)];
                    table[y * w + x] = val;
                }
            }
        }

        long long RectSum(int x0, int y0, int x1, int y1) const {
            x0 = std::max(0, x0); y0 = std::max(0, y0);
            x1 = std::min(w - 1, x1); y1 = std::min(h - 1, y1);
            if (x1 < x0 || y1 < y0) return 0;
            long long res = table[y1 * w + x1];
            if (x0 > 0) res -= table[y1 * w + (x0 - 1)];
            if (y0 > 0) res -= table[(y0 - 1) * w + x1];
            if (x0 > 0 && y0 > 0) res += table[(y0 - 1) * w + (x0 - 1)];
            return res;
        }
    };

    inline NkImage AdaptiveThreshold(const NkImage& src, int blockSize = 31, int offset = 10) {
        auto gray = src.ToGrayscale();
        IntegralImage ii(gray, src.w, src.h);
        NkImage res(src.w, src.h);
        int radius = blockSize / 2;
        for (int y = 0; y < src.h; y++) {
            for (int x = 0; x < src.w; x++) {
                long long sum = ii.RectSum(x - radius, y - radius, x + radius, y + radius);
                int area = (std::min(src.w - 1, x + radius) - std::max(0, x - radius) + 1) *
                           (std::min(src.h - 1, y + radius) - std::max(0, y - radius) + 1);
                uint8_t mean = (uint8_t)(sum / area);
                uint8_t pix = gray[y * src.w + x];
                uint8_t val = (pix < mean - offset) ? 0 : 255;
                res.SetPixel(x, y, val, val, val);
            }
        }
        return res;
    }
}
