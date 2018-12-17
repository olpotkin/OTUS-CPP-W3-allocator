#include "lib/lib.h"
#include "lib/linked_list.h"


int main(int, char *[]) {
  // 1. Define std::map instance with DEFAULT allocator
  // https://en.cppreference.com/w/cpp/container/map
  auto dict = std::map<int, int, std::less<int>, std::allocator<std::pair<const int, int>>>{};

  // 2. Insert 10 elements in std::map (allocated with DEFAULT allocator):
  // @key - values from 0 to 9
  // @value - factorial of key value
  for (auto i = 0; i < 10; ++i) {
    dict.emplace(std::pair<int, int>(i, factorial(i)));
  }

  // 3. Define std::map instance with CUSTOM allocator
  auto dict_custom = std::map<int, int, std::less<int>, logging_allocator<std::pair<const int, int>, 10>>{};

  // 4. Insert 10 elements in std::map (allocated with CUSTOM allocator):
  // @key - values from 0 to 9
  // @value - factorial of key value
  //
  // Implement custom memory allocation for fixed number of map nodes
  // https://en.cppreference.com/w/cpp/named_req/Allocator
  for (auto i = 0; i < 10; ++i) {
    dict_custom.emplace(std::pair<int, int>(i, factorial(i)));
    std::cout << std::endl;
  }

  // 5. Print all elements from dict_custom
  printMap(dict_custom);

  // 6. Define custom container (Linked list) with DEFAULT allocator
  LinkedList<int, std::allocator<int>> list_default;
  // 7. Insert 10 elements from 0 to 9
  for (int i = 0; i < 10; ++i) {
    list_default.push_back(i);
  }

  // 8. Define custom container (Linked list) with CUSTOM allocator
  LinkedList<int, logging_allocator<int, 10>> list_custom;
  // 9. Insert 10 elements from 0 to 9
  for (int i = 0; i < 10; ++i) {
    list_custom.push_back(i);
  }

  // 10. Print all elements from list_custom
  for (auto it = list_custom.cbegin(), itF(list_custom.cend()); it != itF; ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;

/*
  // TEST: Copy constructor
  auto list_cp = list_custom;
  for (auto it = list_cp.cbegin(), itF(list_cp.cend()); it != itF; ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;

  // TEST: Move constructor (with same allocator types)
  auto list_mv = std::move(list_custom);
  for (auto it = list_mv.cbegin(), itF(list_mv.cend()); it != itF; ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;

  // TEST: Move constructor (with different allocator types)
  LinkedList<int, logging_allocator<int, 10>> list_mv2 {std::move(list_default)};
  for (auto it = list_mv2.cbegin(), itF(list_mv2.cend()); it != itF; ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
*/

  return 0;
}
