#pragma once

#include "ImageRetriever.h"
#include <string>


class FileImageRetriever : public ImageRetriever {
public:
  FileImageRetriever(const std::string &file);
  ~FileImageRetriever() = default;

  RGBImage GetImage() const;

public:
  std::string fileName;
};
