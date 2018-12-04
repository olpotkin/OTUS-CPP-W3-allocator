#ifndef ALLOCATOR_LINKED_LIST_H
#define ALLOCATOR_LINKED_LIST_H

#include "lib.h"

template <typename T, typename _A = std::allocator<T>>
class LinkedList {
public:
  struct Node {
    T data;
    Node *next;
  };

  using Allocator = typename _A::template rebind<Node>::other;

  void append(const T& element)
  {
    auto node = alloc.allocate(1);
    node->data = element;
    if (node)
    {
      // List is not empty
      if (head)
      {
        tail->next = node;
        tail = node;
      }
      // List is empty
      else
      {
        head = node;
        tail = node;
      }
    }
  }

  void print()
  {
    Node* disp = head;
    while (disp) {
      std::cout << disp->data << " ";
      disp = disp->next;
    }
    std::cout << std::endl;
  }

private:
  Node *head = nullptr;
  Node *tail = nullptr;
  Allocator alloc;
};

#endif //ALLOCATOR_LINKED_LIST_H
