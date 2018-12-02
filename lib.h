#ifndef ALLOCATOR_LIB_H
#define ALLOCATOR_LIB_H

#include <iostream>
#include <map>


// @class Custom allocator
template<typename T>
struct logging_allocator
{
  using value_type = T;
  using pointer = T*;
  using const_pointer = const T*;
  using reference = T&;
  using const_reference = const T&;

  template<typename U>
  struct rebind
  {
    using other = logging_allocator<U>;
  };

  pointer allocate(std::size_t n)
  {
    std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
    auto p = std::malloc(n * sizeof(T));
    if (!p)
    {
      throw std::bad_alloc();
    }
    return reinterpret_cast<pointer>(p);
  }

  void deallocate(pointer p, std::size_t n)
  {
    std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
    std::free(p);
  }

  template<typename U, typename ...Args>
  void construct(U *p, Args &&...args)
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    new(p) U(std::forward<Args>(args)...);
  };

  void destroy(pointer p)
  {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    p->~T();
  }
};


// @method Calculates factorial for given integer value
int factorial(int value);


// @method Print <key, value> pairs of map
void printMap(std::map<int, int, std::less<int>, logging_allocator<std::pair<const int, int>>>& dict);

#endif //ALLOCATOR_LIB_H
