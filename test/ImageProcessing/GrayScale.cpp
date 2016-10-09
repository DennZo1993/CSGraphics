#include "gtest/gtest.h"
#include "ImageProcessing.h"


TEST(GrayScaleImage, RedToGray) {
  // Red pixels to gray scale.
  RGBImage rgb(4, 5, RGBAPixel(100,0,0));
  GrayScaleImage gray = RGBToGray(rgb);

  ASSERT_EQ(4, gray.getHeight());
  ASSERT_EQ(5, gray.getWidth());
  for (const auto &p : gray) {
    ASSERT_EQ(21, p);
  }
}


TEST(GrayScaleImage, GreenToGray) {
  // Red pixels to gray scale.
  RGBImage rgb(4, 5, RGBAPixel(0,100,0));
  GrayScaleImage gray = RGBToGray(rgb);

  for (const auto &p : gray) {
    ASSERT_EQ(72, p);
  }
}


TEST(GrayScaleImage, BlueToGray) {
  // Red pixels to gray scale.
  RGBImage rgb(4, 5, RGBAPixel(0,0,100));
  GrayScaleImage gray = RGBToGray(rgb);

  for (const auto &p : gray) {
    ASSERT_EQ(7, p);
  }
}


TEST(GrayScaleImage, WhiteToGray) {
  // Red pixels to gray scale.
  RGBImage rgb(4, 5, RGBAPixel::PureWhite);
  GrayScaleImage gray = RGBToGray(rgb);

  for (const auto &p : gray) {
    ASSERT_EQ(255, p);
  }
}


TEST(GrayScaleImage, BlackToGray) {
  // Red pixels to gray scale.
  RGBImage rgb(4, 5, RGBAPixel::PureBlack);
  GrayScaleImage gray = RGBToGray(rgb);

  for (const auto &p : gray) {
    ASSERT_EQ(0, p);
  }
}

