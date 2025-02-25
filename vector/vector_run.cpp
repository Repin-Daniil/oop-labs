#include <assert.h>
#include <vector.h>
#include <iostream>
#include <vector>

int main() {
  using container::vector;

  { vector<int> v(10, 1); }

  // vector<int> v(1000, 11);
  // v.clear();
  // assert(v.size() == 0u);
  // assert(v.empty());

  return EXIT_SUCCESS;
}