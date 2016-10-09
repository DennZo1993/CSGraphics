#include "ImageProcessing.h"
#include <cmath> // std::lround


GrayScaleImage RGBToGray(const RGBImage &input) {
  GrayScaleImage result(input.getHeight(), input.getWidth());

  for (size_t i = 0; i < input.getSize(); ++i) {
    result[i] =
      std::lround(0.21 * input[i].r + 0.72 * input[i].g + 0.07 * input[i].b);
  }

  return result;
}


// TODO IntegralImage GrayScaleToIntegral(const GrayScaleImage &input) {}


// TODO BinaryImage ThresholdImage(const IntegralImage &input) {}


/*  FIXME Uncomment when core ThresholdImage function is implemented.
BinaryImage ThresholdImage(const GrayScaleImage &input) {
  return ThresholdImage(GrayScaleToIntegral(input));
}


BinaryImage ThresholdImage(const RGBImage &input) {
  return ThresholdImage(GrayScaleToIntegral(RGBToGray(input)));
}
*/
