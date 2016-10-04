#pragma once

#include <iostream>
#include <stdexcept>

// Class representing 3-channel pixel in RGB model + alpha channel.
// Ordering is straight: R,G,B,A (sufficient for [] operators).

class RGBAPixel {
public:
  using PixelType = unsigned char;

  // Black fully non-transparent pixel.
  RGBAPixel(PixelType _r = MIN_VALUE, PixelType _g = MIN_VALUE,
            PixelType _b = MIN_VALUE, PixelType _a = MAX_VALUE)
    : r(_r), g(_g), b(_b), a(_a) {}

  // This class doesn't store complex objects with non-trivial logic,
  // so default constructors/assignment operators must be okay.
  RGBAPixel(const RGBAPixel &other) = default;
  RGBAPixel(RGBAPixel &&other) = default;
  ~RGBAPixel() = default;

  RGBAPixel& operator=(const RGBAPixel &other) = default;
  RGBAPixel& operator=(RGBAPixel &&other) = default;

  // Subscript operators throw std::invalid_argument for i >= 3.
  PixelType& operator[](size_t i);
  const PixelType& operator[](size_t i) const;

  // FIXME Input/output operators are currently incompatible: << writes '(' and
  // stuff, while >> expects R G B A as unsigned chars (might me a problem too).
  // Think of better text representation @DennZo1993.
  friend std::istream& operator>>(std::istream &is, RGBAPixel &p);
  friend std::ostream& operator<<(std::ostream &os, const RGBAPixel &p);

  bool operator==(const RGBAPixel &other) const;
  bool operator!=(const RGBAPixel &other) const;

  // Just simple arithmetic addition.
  RGBAPixel& operator+=(const RGBAPixel &other);
  RGBAPixel& operator-=(const RGBAPixel &other);
  friend RGBAPixel operator+(RGBAPixel lhs, const RGBAPixel &rhs);
  friend RGBAPixel operator-(RGBAPixel lhs, const RGBAPixel &rhs);

public:
  PixelType r;
  PixelType g;
  PixelType b;
  PixelType a;

private:
  static constexpr PixelType MIN_VALUE = 0;
  static constexpr PixelType MAX_VALUE = 255;
};

