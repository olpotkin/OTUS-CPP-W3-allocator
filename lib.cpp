#include "lib.h"


int factorial(int value)
{
  return (value == 1 || value == 0) ? 1 : factorial(value - 1) * value;
}

void printMap(std::map<int, int> dict)
{
  std::cout << "---------------" << std::endl;
  // Iterate through the dictionary and print pairs <key, value>
  auto it = dict.begin();
  while (it != dict.end())
  {
    std::cout << "<" << it->first << ", " << it->second << ">" << std::endl;
    ++it;
  }
  std::cout << "---------------" << std::endl;
}
