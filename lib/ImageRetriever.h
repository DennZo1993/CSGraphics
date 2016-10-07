#pragma once

#include "RGBImage.h"


// Simple image retriever interface.
// Returns an RGB image.
class ImageRetriever {
public:
  ImageRetriever() {}
  virtual ~ImageRetriever() {}

  virtual RGBImage GetImage() const = 0;
};
