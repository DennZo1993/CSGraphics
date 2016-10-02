#include "Image.h"
#include <iostream>

int main() {
  Image<int> testImage(4, 5, 10);
  std::cout << testImage << std::endl;
  return 0;
}
