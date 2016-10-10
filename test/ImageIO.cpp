#include "gtest/gtest.h"
#include "ImageIO.h"
#include "ImageProcessing.h"


TEST(ImageIO, WriteRGBImageGood) {
  // Valid file name.
  RGBImage img = ImageIO::ReadImage("test_data/pictures/alley_1_frame_0001.png");
  ImageIO::WriteImage(img, "rgb_01.png");
}


TEST(ImageIO, WriteRGBImageBad) {
  // Invalid file name.
  RGBImage img = ImageIO::ReadImage("test_data/pictures/alley_1_frame_0001.png");
  ASSERT_THROW(ImageIO::WriteImage(img, "bad_dir/rgb_01.png"), std::runtime_error);
}


TEST(ImageIO, WriteGrayScale) {
  RGBImage img = ImageIO::ReadImage("test_data/pictures/alley_1_frame_0001.png");
  ImageIO::WriteImage(RGBToGray(img), "gray_01.png");
}
