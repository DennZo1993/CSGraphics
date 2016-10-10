#include "FileImageRetriever.h"
#include "ImageIO.h"


FileImageRetriever::FileImageRetriever(const std::string &file)
  : ImageRetriever()
  , fileName(file)
{
}


RGBImage FileImageRetriever::GetImage() const {
  return ImageIO::ReadImage(fileName);
}
