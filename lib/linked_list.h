#ifndef ALLOCATOR_LINKED_LIST_H
#define ALLOCATOR_LINKED_LIST_H

#include "lib.h"


// Element of the linked list
template<typename T>
struct Node {
  Node* next;
  T data;
  Node() : next(nullptr), data(T()) {};
};

// Iterator for Linked List traversal (const specialization)
// https://en.cppreference.com/w/cpp/iterator/iterator_traits
// http://labmaster.mi.infn.it/Laboratorio2/serale/www.sgi.com/tech/stl/ForwardIterator.html
template <typename T>
struct ListIterator {
  using value_type = T;
  using pointer = const T*;
  using reference = const T&;
  using iterator_category = std::forward_iterator_tag;

  using _self = ListIterator<T>;
  Node<T>* _node;

  // Default constructor
  ListIterator() : _node(nullptr) {};

  // Parametrized constructor
  ListIterator(Node<T>* pNode) : _node(pNode) {};

  // Get a reference for an object
  reference operator*() const {
    return _node->data;
  }

  // Get a pointer for an object
  pointer operator->() const {
    return &(_node->data);
  }

  // Increment - next element of the container
  _self& operator++() {
    if (_node == nullptr) {
      return *this;
    }
    else {
      _node = _node->next;
    }
    return *this;
  }

  // Comparison operators
  bool operator==(const _self& rhs) const {
    return _node == rhs._node;
  }

  bool operator!=(const _self& rhs) const {
    return _node != rhs._node;
  }
};

// Custom data structure - Linked List (single connection)
template <typename T, typename _A = std::allocator<T>>
class LinkedList {
public:
  // Constructor
  LinkedList(): head(nullptr), tail(nullptr), _alloc() {};

  // Destructor
  ~LinkedList() {
    auto current = head;
    while (current != nullptr) {
      auto p_rm = current;
      current = current->next;
      _alloc.destroy(p_rm);
      _alloc.deallocate(p_rm, 1);
    }
  }

  using Allocator = typename _A::template rebind< Node<T> >::other;

  Node<T>* constructNode(const T& value) {
    // Allocate memory for a new Node
    auto ptr = _alloc.allocate(1);
    _alloc.construct(ptr);

    // Set parameters for a new Node
    ptr->data = value;
    ptr->next = nullptr;

    return ptr;
  }

  // Append new Node in the end of the Linked List
  void push_back(const T& value) {
    auto new_node = constructNode(value);

    // If List is empty
    if (head == nullptr) {
      head = new_node;
      tail = new_node;
    }
    else {
      tail->next = new_node;
      tail = new_node;
      tail->next = nullptr;
    }
  }

  ListIterator<T> cbegin() const noexcept {
    return ListIterator<T>(head);
  }

  ListIterator<T> cend() noexcept {
    return ListIterator<T>();
  }

private:
  Node<T>* head = nullptr;
  Node<T>* tail = nullptr;
  Allocator _alloc;
};

#endif //ALLOCATOR_LINKED_LIST_H
