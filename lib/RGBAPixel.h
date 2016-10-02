#pragma once

class RGBAPixel {
public:
  using PixelType = unsigned char;

  RGBAPixel(PixelType _r = MIN_VALUE, PixelType _g = MIN_VALUE,
            PixelType _b = MIN_VALUE, PixelType _a = MAX_VALUE)
    : r(_r), g(_g), b(_b), a(_a) {}

  PixelType& operator[](size_t i) {
    switch (i) {
    case 0: return r;
    case 1: return g;
    case 2: return b;
    case 3: return a;
    default: throw std::invalid_argument("Color channel index is invalid!");
    }
  }

  const PixelType& operator[](size_t i) const {
    switch (i) {
    case 0: return r;
    case 1: return g;
    case 2: return b;
    case 3: return a;
    default: throw std::invalid_argument("Color channel index is invalid!");
    }
  }

  friend std::ostream& operator<<(std::ostream &os, const RGBPixel &p) {
    os << '(' << (int)p.r << ',' << (int)p.g << ',' << (int)p.b << ')';
    return os;
  }

  PixelType r;
  PixelType g;
  PixelType b;
  PixelType a;

private:
  static constexpr PixelType MIN_VALUE = 0;
  static constexpr PixelType MAX_VALUE = 255;
};

