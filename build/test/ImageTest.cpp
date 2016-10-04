#include "gtest/gtest.h"
#include "Image.h"


TEST(Image, DefaultConstruction) {
  Image<int> img;
  ASSERT_EQ(0, img.getHeight());
  ASSERT_EQ(0, img.getWidth());
  ASSERT_EQ(0, img.getSize());
  ASSERT_TRUE(img.isEmpty());
}


TEST(Image, NonDefaultConstructor) {
  Image<double> img(2, 2, 1.1);
  ASSERT_EQ(2, img.getHeight());
  ASSERT_EQ(2, img.getWidth());
  ASSERT_EQ(4, img.getSize());
  ASSERT_EQ(1.1, img[1]);
  ASSERT_THROW(img[5], std::out_of_range);
}


TEST(Image, Comparison){
  Image<int> img1(2, 2, 1);
  Image<int> img2(2, 2, 1);
  Image<int> img3;
  ASSERT_TRUE(img1 == img2);
  ASSERT_TRUE(img2 == img1);
  ASSERT_FALSE(img1 == img3);
  ASSERT_FALSE(img3 == img1);
  ASSERT_TRUE(img2 != img3);
  ASSERT_TRUE(img3 != img2);
}


TEST(Image, CopyConstructor) {
  Image<int> img1(2, 2, 1);
  Image<int> img2(img1);
  Image<int> img3;

  ASSERT_EQ(img1, img2);

  img3 = img1;
  ASSERT_EQ(img1, img3);
}


TEST(Image, SubscriptOperationNonConst) {
  Image<int> img(2, 2, 1);
  img[0] = 3;
  img[1] = 3;
  img[2] = 3;
  img[3] = 3;

  ASSERT_EQ(Image<int>(2, 2, 3), img);
  ASSERT_THROW(img[4] = 10, std::out_of_range);
}


TEST(Image, Addition) {
  Image<int> img1(2, 2, 1);
  Image<int> img2(2, 2, 2);

  img1 += img2;
  ASSERT_EQ(Image<int>(2, 2, 3), img1);

  img1 = img1 + img2;
  ASSERT_EQ(Image<int>(2, 2, 5), img1);
}


TEST(Image, Subtraction) {
  Image<int> img1(2, 2, 5);
  Image<int> img2(2, 2, 1);

  img1 -= img2;
  ASSERT_EQ(Image<int>(2, 2, 4), img1);

  img1 = img1 - img2;
  ASSERT_EQ(Image<int>(2, 2, 3), img1);
}

TEST(Image, MatchingOperation) {
  Image<int> img(2, 2, 1);
  img[0] = 1;
  img[1] = 2;
  img[2] = 3;
  img[3] = 4;

  ASSERT_EQ(4, img(1, 1));
  ASSERT_EQ(img[2], img(1, 0)); 
}