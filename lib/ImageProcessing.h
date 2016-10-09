#pragma once

#include "ImageTypes.h"


// Convert RGB image to gray scale.
GrayScaleImage RGBToGray(const RGBImage &input);

// Create an integral image from gray scale.
IntegralImage GrayScaleToIntegral(const GrayScaleImage &input);

// Convert an integral image to binary.
// The core thresholding function.
BinaryImage ThresholdImage(const IntegralImage &input);

// Convert a gray scale image to binary.
// First creates an IntegralImage, then calls the core thresholding function.
BinaryImage ThresholdImage(const GrayScaleImage &input);

// Convert an RGB image to binary.
BinaryImage ThresholdImage(const RGBImage &input);

