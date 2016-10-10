#pragma once

#include "ImageTypes.h"
#include "lodepng/lodepng.h"
#include <string>


namespace ImageIO {

RGBImage ReadImage(const std::string &fileName);

void WriteImage(const RGBImage       &image, const std::string &fileName);
void WriteImage(const BinaryImage    &image, const std::string &fileName);
void WriteImage(const GrayScaleImage &image, const std::string &fileName);

} // namespace ImageIO
