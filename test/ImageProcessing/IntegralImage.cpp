#include "gtest/gtest.h"
#include "ImageProcessing.h"


TEST(IntegralImage, EmptyImage) {
  GrayScaleImage gray;
  IntegralImage img = GrayScaleToIntegral(gray);

  ASSERT_EQ(0, img.getHeight());
  ASSERT_EQ(0, img.getWidth());
  ASSERT_EQ(0, img.getSize());
  ASSERT_TRUE(img.isEmpty());
}


TEST(IntegralImage, SinglePixelImage) {
  GrayScaleImage gray(1, 1, 10);
  IntegralImage img = GrayScaleToIntegral(gray);

  ASSERT_EQ(IntegralImage(1, 1, 10), img);
}


TEST(IntegralImage, SingleRowImage) {
  GrayScaleImage gray(1, 10, 1);
  IntegralImage img = GrayScaleToIntegral(gray);

  ASSERT_EQ(1, img.getHeight());
  ASSERT_EQ(10, img.getWidth());
  for (size_t j = 0; j < img.getWidth(); ++j) {
    ASSERT_EQ(j + 1, img(0, j));
  }
}


TEST(IntegralImage, SingleColumnImage) {
  GrayScaleImage gray(10, 1, 1);
  IntegralImage img = GrayScaleToIntegral(gray);

  ASSERT_EQ(10, img.getHeight());
  ASSERT_EQ(1, img.getWidth());
  for (size_t i = 0; i < img.getWidth(); ++i) {
    ASSERT_EQ(i + 1, img(i, 0));
  }
}


TEST(IntegralImage, FullSizeImage) {
  GrayScaleImage gray(10, 10, 1);
  IntegralImage img = GrayScaleToIntegral(gray);

  ASSERT_EQ(10, img.getHeight());
  ASSERT_EQ(10, img.getWidth());
  for (size_t i = 0; i < img.getHeight(); ++i)
    for (size_t j = 0; j < img.getWidth(); ++j) {
      ASSERT_EQ((i+1) * (j+1), img(i, j));
    }
}

