#include "lib.h"
#include <vector>


int main(int, char *[])
{
  // 1. Define std::map instance with DEFAULT allocator
  // https://en.cppreference.com/w/cpp/container/map
  auto dict = std::map<int, int, std::less<int>, std::allocator<std::pair<const int, int>>>{};

  // 2. Insert 10 elements in std::map (allocated with DEFAULT allocator):
  // @key - values from 0 to 9
  // @value - factorial of key value
  for (auto i = 0; i < 10; ++i)
  {
    dict[i] = factorial(i);
  }

  // 3. Define std::map instance with CUSTOM allocator
  auto dict_custom = std::map<int, int, std::less<int>, logging_allocator<std::pair<const int, int>, 10>>{};

  // 4. Insert 10 elements in std::map (allocated with CUSTOM allocator):
  // @key - values from 0 to 9
  // @value - factorial of key value
  //
  // Implement custom memory allocation for fixed number of map nodes
  // https://en.cppreference.com/w/cpp/named_req/Allocator
  for (auto i = 0; i < 10; ++i)
  {
    dict_custom[i] = factorial(i);
    std::cout << std::endl;
  }

  // 5. Print all elements from dict_custom
  printMap(dict_custom);

  return 0;
}
