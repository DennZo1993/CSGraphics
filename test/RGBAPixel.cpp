#include "gtest/gtest.h"
#include "RGBAPixel.h"


TEST(RGBAPixel, DefaultConstruction) {
  RGBAPixel p;

  ASSERT_EQ(0, p.r);
  ASSERT_EQ(0, p.g);
  ASSERT_EQ(0, p.b);
  ASSERT_EQ(255, p.a);
}


TEST(RGBAPixel, Comparison) {
  RGBAPixel p1(10, 10, 10, 255);
  RGBAPixel p2(10, 10, 10, 255);
  RGBAPixel p3;

  ASSERT_TRUE(p1 == p2);
  ASSERT_TRUE(p2 == p1);
  ASSERT_FALSE(p1 == p3);
  ASSERT_FALSE(p3 == p1);
  ASSERT_TRUE(p2 != p3);
  ASSERT_TRUE(p3 != p1);
}


TEST(RGBAPixel, CopyConstruction) {
  RGBAPixel p1(10, 20, 30, 200);
  RGBAPixel p2(p1);

  ASSERT_EQ(p1, p2);
}


TEST(RGBAPixel, SubscriptOperationConst) {
  RGBAPixel p(10, 20, 30, 100);

  ASSERT_EQ(10, p[0]);
  ASSERT_EQ(20, p[1]);
  ASSERT_EQ(30, p[2]);
  ASSERT_EQ(100, p[3]);
  ASSERT_THROW(p[4], std::invalid_argument);
}


TEST(RGBAPixel, SubscriptOperationNonConst) {
  RGBAPixel p(10, 20, 30, 100);
  p[0] = 15;
  p[1] = 25;
  p[2] = 35;
  p[3] = 200;

  ASSERT_EQ(RGBAPixel(15, 25, 35, 200), p);
  ASSERT_THROW(p[4] = 10, std::invalid_argument);
}


TEST(RGBAPixel, Addition) {
  RGBAPixel p1(10, 20, 30, 40);
  RGBAPixel p2(5, 5, 5, 5);

  p1 += p2;
  ASSERT_EQ(RGBAPixel(15, 25, 35, 45), p1);

  p1 = p1 + p2;
  ASSERT_EQ(RGBAPixel(20, 30, 40, 50), p1);
}


TEST(RGBAPixel, Subtraction) {
  RGBAPixel p1(10, 20, 30, 40);
  RGBAPixel p2(5, 5, 5, 5);

  p1 -= p2;
  ASSERT_EQ(RGBAPixel(5, 15, 25, 35), p1);

  p1 = p1 - p1;
  ASSERT_EQ(RGBAPixel(0, 0, 0, 0), p1);
}
