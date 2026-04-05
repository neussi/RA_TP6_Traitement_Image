#include <Unitest/Unitest.h>
#include <Unitest/TestMacro.h>
#include "../Image.h"

using namespace NkMath;

TEST_CASE(TP6, ImageCreation) {
    NkImage img(100, 100);
    ASSERT_EQUAL(img.w, 100);
    ASSERT_EQUAL(img.h, 100);
    ASSERT_EQUAL(img.data.size(), 100u * 100u * 4u);
}

TEST_CASE(TP6, GrayscaleConversion) {
    NkImage img(2, 2);
    img.SetPixel(0, 0, 255, 255, 255); // White
    img.SetPixel(1, 1, 0, 0, 0);       // Black
    auto gray = img.ToGrayscale();
    ASSERT_EQUAL(gray[0], 255);
    ASSERT_EQUAL(gray[3], 0);
}

TEST_CASE(TP6, IntegralImage) {
    std::vector<uint8_t> gray = {1, 2, 3, 4}; // 2x2
    IntegralImage ii(gray, 2, 2);
    // Table should be:
    // 1  3
    // 4  10
    ASSERT_EQUAL(ii.RectSum(0, 0, 0, 0), 1LL);
    ASSERT_EQUAL(ii.RectSum(1, 1, 1, 1), 4LL);
    ASSERT_EQUAL(ii.RectSum(0, 0, 1, 1), 10LL);
}

TEST_CASE(TP6, AdaptiveThreshold) {
    NkImage img(10, 10);
    for(int i=0; i<100; i++) img.data[i*4]=128; // Gray
    img.SetPixel(5, 5, 0, 0, 0); // Black spot
    
    NkImage bin = AdaptiveThreshold(img, 3, 5);
    ASSERT_EQUAL(bin.data[(5*10+5)*4], 0); // Should remain black
}
