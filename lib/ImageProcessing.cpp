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


IntegralImage GrayScaleToIntegral(const GrayScaleImage &input) {
  // In integral I pixel I(y,x) stores sum of input's pixels in square area
  // from (0,0) to (y,x).
  // So, I(y,x) = input(y,x) + I(y-1,x) + I(y,x-1) - I(y-1,x-1)

  // If input is empty, return empty image.
  if (input.isEmpty())
    return IntegralImage();

  IntegralImage result(input.getHeight(), input.getWidth(), 0);

  result(0, 0) = input(0, 0);

  // First fill 0th row and 0th column.
  for (size_t x = 1; x < input.getWidth(); ++x)
    result(0, x) = input(0, x) + result(0, x-1);

  for (size_t y = 1; y < input.getHeight(); ++y)
    result(y, 0) = input(y, 0) + result(y-1, 0);

  for (size_t y = 1; y < input.getHeight(); ++y)
    for (size_t x = 1; x < input.getWidth(); ++x) {
      result(y, x) =
        input(y, x) + result(y, x-1) + result(y-1, x) - result(y-1, x-1);
    }

  return result;
}


// TODO BinaryImage ThresholdImage(const IntegralImage &input) {}


/*  FIXME Uncomment when core ThresholdImage function is implemented.
BinaryImage ThresholdImage(const GrayScaleImage &input) {
  return ThresholdImage(GrayScaleToIntegral(input));
}


BinaryImage ThresholdImage(const RGBImage &input) {
  return ThresholdImage(GrayScaleToIntegral(RGBToGray(input)));
}
*/
