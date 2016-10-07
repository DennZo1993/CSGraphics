#include "gtest/gtest.h"
#include "FileImageRetriever.h"


TEST(FileImageRetriever, ExistingFile) {
  FileImageRetriever fir("test_data/pictures/alley_1_frame_0001.png");
  RGBImage img = fir.GetImage();

  ASSERT_EQ(436, img.getHeight());
  ASSERT_EQ(1024, img.getWidth());
}


TEST(FileImageRetriever, MissingFile) {
  FileImageRetriever fir("fissing_file");

  ASSERT_THROW(fir.GetImage(), std::runtime_error);
}


TEST(FileImageRetriever, ImageContent) {
  FileImageRetriever fir("test_data/pictures/small_4x5_color.png");
  RGBImage img = fir.GetImage();

  ASSERT_EQ(4, img.getHeight());
  ASSERT_EQ(5, img.getWidth());

  for (size_t j = 0; j < img.getWidth(); ++j) {
    // First row is black.
    ASSERT_EQ(RGBAPixel::PureBlack, img(0,j));
    // Second row - red.
    ASSERT_EQ(RGBAPixel::PureRed,   img(1,j));
    // Third row - green.
    ASSERT_EQ(RGBAPixel::PureGreen, img(2,j));
    // Fourth row - white.
    ASSERT_EQ(RGBAPixel::PureWhite, img(3,j));
  }
}
