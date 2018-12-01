#include "lib.h"


int main()
{
  // 1. Define std::map instance with default allocator
  // https://en.cppreference.com/w/cpp/container/map
  std::map<int, int, std::less<int>, std::allocator<std::pair<const int, int>>> dict;

  // 2. Insert 10 elements in std::map:
  // @key - values from 0 to 9
  // @value - factorial of key value
  for (auto i = 0; i < 1; ++i)
  {
    dict[i] = factorial(i);
  }
  printMap(dict);

  return 0;
}
