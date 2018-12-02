#include "lib.h"


int factorial(int value)
{
  return (value == 1 || value == 0) ? 1 : factorial(value - 1) * value;
}

void printMap(std::map<int, int, std::less<int>, logging_allocator<std::pair<const int, int>>>& dict)
{
  // Iterate through the dictionary and print pairs <key, value>
  for(const auto& node: dict)
  {
    std::cout << node.first << " " << node.second << std::endl;
  }
}
