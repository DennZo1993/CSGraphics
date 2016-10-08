#include "FileImageRetriever.h"
#include "lodepng/lodepng.h"

#include <vector>
#include <stdexcept>


FileImageRetriever::FileImageRetriever(const std::string &file)
  : ImageRetriever()
  , fileName(file)
{
}


RGBImage FileImageRetriever::GetImage() const {
  RGBImage result;

  std::vector<RGBAPixel::PixelType> png;
  std::vector<RGBAPixel::PixelType> image;
  unsigned width = 0, height = 0;

  if (lodepng::load_file(png, fileName))
    throw std::runtime_error("Error loading PNG file " + fileName);
  if (lodepng::decode(image, width, height, png))
    throw std::runtime_error("Error decoding PNG file " + fileName);

  result.Resize(height, width);

  for (size_t i = 0; i < result.getSize(); ++i) {
    auto r = image[4 * i + 0];
    auto g = image[4 * i + 1];
    auto b = image[4 * i + 2];
    auto a = image[4 * i + 3];
    result[i] = RGBAPixel(r, g, b, a);
  }

  return result;
}
