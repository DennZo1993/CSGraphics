#pragma once

#include <stdexcept>
#include <cassert>
#include <cmath>      // std::abs
#include <iostream>
#include <algorithm>
#include <chrono>
#include <fstream>


template <class T>
class Image {
// ==========
// Constructors and destructor.
// ==========

public:

  Image() : Height(0), Width(0), data(nullptr) {}


  // Creates a new image and fills it with \p value.
  // Throws std::bad_alloc, std::invalid_argument.
  Image(int h, int w, const T &value) : data(nullptr) {
    AllocateAndFill(h, w, value);
  }


  Image(const Image<T> &other) : data(nullptr) {
    DeepCopyFrom(other);
  }


  Image(Image<T> &&other) : Image<T>() {
    swap(*this, other);
  }


  virtual ~Image() {
    Destroy();
  }

// ==========
// Allocation and destruction.
// ==========

public:

  // Destroy the Image and allocate data with new size.
  // Data will be uninitialized after this operation.
  // Throws std::invalid_argument, std::bad_alloc.
  void Allocate(int h, int w) {
    Destroy();
    // Negative size is a logical error.
    if (h < 0 || w < 0)
      throw std::invalid_argument("Either height or width is less than 0!");

    // Logically reallocation with either dimension equal to 0 is destruction.
    if (h == 0 || w == 0)
      return;

    Height = h;
    Width = w;

    try {
      data = new T[Height * Width];
    } catch (...) {
      Destroy();
      throw;
    }
  }


  // TODO consider using memcpy.
  void DeepCopyFrom(const Image<T> &other) {
    Allocate(other.getHeight(), other.getWidth());

    // We're possibly copying from an empty image. Then image must become
    // empty too. This is the only normal way to get empty.
    if (isEmpty()) {
      assert(other.isEmpty() && "Empty image after copy from non-empty one!");
      return;
    }

    assert(data && "Data is NULL!");
    for (size_t i = 0; i < Height * Width; ++i)
      data[i] = other[i];
  }

protected:

  // Free allocated memory. Set dimensions to 0, data to nullptr.
  void Destroy() {
    delete[] data;
    Height = Width = 0;
  }

// ==========
// Filling the values.
// ==========
//
// These functions should NOT allocate/free memory.

public:


  // Fill the whole image with the given value.
  void Fill(const T &value) {
    assert(((data && Height && Width) || (!data && !Height && !Width)) &&
           "Null data with non-zero dimensions or vice versa!");

    for (size_t i = 0; i < Height * Width; ++i)
        data[i] = value;
  }


  // Throws std::bad_alloc, std::invalid_argument.
  void AllocateAndFill(int h, int w, const T &value) {
    // This must be logically safe to just call Fill() as it must never fail:
    // if image gets empty after Allocate (<=> h and/or w is 0), Fill() must
    // do nothing.
    Allocate(h, w);
    Fill(value);
  }


// ==========
// Reading / writing.
// ==========
//
// Read functions reallocate memory.

public:

  // Reads the input stream as plain text image.
  // Extension of the file name is NOT considered!
  //
  // Format:
  //   * 2 integers: height and width respectively;
  //   * <height>*<width> values separated by a whitespace.
  //
  // Throws sts::bad_alloc, std::invalid_argument, std ios exceptions.
  friend std::istream &operator >>(std::istream &is, Image<T> &m) {
    std::ios_base::sync_with_stdio(false);
    is.exceptions(std::ios_base::failbit | std::ios_base::badbit);
    // Signed int to avoid reading negative numbers.
    long h = 0, w = 0;
    is >> h >> w;
    // If we couldn't read both height and width, exception had been thrown.

    m.Allocate(h, w);

    // Here we safely cast to size_t, because negative h or w must have resulted
    // in exception in Allocate().
    for (size_t i = 0; i < static_cast<size_t>(h * w); ++i) {
        // If stream containes less data than declared - stop reading.
        if (!is.good())
          break;

        is >> m[i];
      }

    return is;
  }


  friend std::ostream &operator <<(std::ostream &os, const Image<T> &m) {
    std::ios_base::sync_with_stdio(false);
    os.exceptions(std::ios_base::failbit | std::ios_base::badbit);

    os << m.getHeight() << ' ' << m.getWidth() << '\n';
    for (size_t i = 0; i < m.getHeight(); ++i) {
      for (size_t j = 0; j < m.getWidth(); ++j) {
        os << m(i,j) << ' ';
      }
      os << '\n';
    }
    return os;
  }

// ==========
// Data accessors.
// ==========

public:

  // Throws std::out_of_range.
  T& operator()(size_t i, size_t j) {
    assert(data && "Subscript operation on null data!");
    if (i >= Height)
      throw std::out_of_range("i (" + std::to_string(i) +
                              ") is greater than height (" +
                              std::to_string(Height) + ")");
    if (j >= Width)
      throw std::out_of_range("j (" + std::to_string(j) +
                              ") is greater than width (" +
                              std::to_string(Width) + ")");
    return data[i * Width + j];
  }


  const T& operator()(size_t i, size_t j) const {
    assert(data && "Subscript operation on null data!");
    if (i >= Height)
      throw std::out_of_range("i (" + std::to_string(i) +
                              ") is greater than height (" +
                              std::to_string(Height) + ")");
    if (j >= Width)
      throw std::out_of_range("j (" + std::to_string(j) +
                              ") is greater than width (" +
                              std::to_string(Width) + ")");
    return data[i * Width + j];
  }


  T& operator[](size_t i) {
    if (i >= Height * Width)
      throw std::out_of_range("Linear index " + std::to_string(i) +
                              ") is out of range");
    return data[i];
  }


  const T& operator[](size_t i) const {
    if (i >= Height * Width)
      throw std::out_of_range("Linear index " + std::to_string(i) +
                              ") is out of range");
    return data[i];
  }


  inline size_t getHeight() const { return Height;         }
  inline size_t getWidth()  const { return Width;          }
  inline size_t getSize()   const { return Height * Width; }

  inline bool isEmpty() const {
    assert(((!data && !Height && !Width) || (data && Height && Width)) &&
           "Either non-zero size with empty data or vice versa!");
    return data == nullptr;
  }

// ==========
// Assignment / cast.
// ==========

public:

  Image<T> &operator=(Image<T> other) {
    swap(*this, other);
    return *this;
  }


  friend void swap(Image<T> &first, Image<T> &second) {
    using std::swap;
    swap(first.Height, second.Height);
    swap(first.Width, second.Width);
    swap(first.data, second.data);
  }


  // Cast.
  template<class U>
  Image<U> castTo() const {
    Image<U> result(Height, Width, 0);

    for (size_t i = 0; i < Height * Width; ++i)
      result[i] = static_cast<U>(data[i]);

    return result;
  }

// ==========
// Comparison operators.
// ==========
  bool operator==(const Image<T> &other) const {
    // Not actually needed check, but let's make this explicit for readability.
    if (isEmpty() != other.isEmpty())
      return false;
    if (Height != other.getHeight() || Width != other.getWidth())
      return false;

    for (size_t i = 0; i < Height * Width; ++i)
      if (data[i] != other[i])
        return false;
    return true;
  }


  bool operator!=(const Image<T> &other) const {
    return !(*this == other);
  }

// ==========
// Arithmetic operators.
// ==========

  // Throws std::invalid_argument.
  Image<T> &operator+=(const Image<T> &other) {
    if (Height != other.getHeight() ||
        Width != other.getWidth())
      throw std::invalid_argument("Image size mismatch in += operation!");

    // If both imagees are empty, we are done.
    if (isEmpty())
      return *this;

    for (size_t i = 0; i < Height * Width; ++i)
      data[i] += other[i];

    return *this;
  }


  // Throws std::invalid_argument.
  Image<T> &operator-=(const Image<T> &other) {
    if (Height != other.getHeight() ||
        Width != other.getWidth())
      throw std::invalid_argument("Image size mismatch in -= operation!");

    // If both imagees are empty, we are done.
    if (isEmpty())
      return *this;

    for (size_t i = 0; i < Height * Width; ++i)
      data[i] -= other[i];

    return *this;
  }


  // Throws std::invalid_argument.
  friend Image<T> operator+(Image<T> lhs, const Image<T> &rhs) {
    lhs += rhs;
    return lhs;
  }


  // Throws std::invalid_argument.
  friend Image<T> operator-(Image<T> lhs, const Image<T> &rhs) {
    lhs -= rhs;
    return lhs;
  }


protected:

  size_t Height;
  size_t Width;
  T *data;
};

