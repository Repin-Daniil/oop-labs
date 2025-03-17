#include <assert.h>
#include <vector.h
#include <iostream>
#include <vector>

int main() {
  using container::vector;

  vector<std::unique_ptr<int>> v;
  for (int i = 0; i < 100; ++i) {
    v.push_back(std::make_unique<int>(i));
  }

  return EXIT_SUCCESS;
}