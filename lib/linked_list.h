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
  LinkedList(): head(nullptr), tail(nullptr), _alloc() {
    std::cout << "LOG: LL ctor..." << std::endl;
  };

  // Copy Constructor (with same allocator types)
  LinkedList(const LinkedList &src)
    : head(nullptr), tail(nullptr), _alloc() {
    std::cout << "LOG: LL COPY ctor..." << std::endl;
    copyList(src);
  }

  // Copy Constructor (with different allocator types)
  template <typename TAlloc>
  LinkedList(const LinkedList<T, TAlloc> &src)
    : head(nullptr), tail(nullptr), _alloc() {
    std::cout << "LOG: LL COPY ctor (diff allocs)..." << std::endl;
    copyList(src);
  }

  // @method
  // Helper for copying elements between Linked Lists
  template <typename TAlloc>
  void copyList(const LinkedList<T, TAlloc> &src) {
    Node<T>* curNode = src.cbegin()._node;
    while (curNode != nullptr) {
      this->push_back(curNode->data);
      curNode = curNode->next;
    }
  }

  // Move Constructor (with same allocator types)
  LinkedList(LinkedList &&src)
    : head(src.head), tail(src.tail), _alloc(src._alloc) {
    std::cout << "LOG: LL MOVE ctor..." << std::endl;
    src.head = nullptr;
    src.tail = nullptr;
  }

  // Move Constructor (with different allocator types)
  template <typename TAlloc>
  LinkedList(LinkedList<T, TAlloc>&& src)
    : head(nullptr), tail(nullptr), _alloc() {
    std::cout << "LOG: LL MOVE ctor (diff allocs)..." << std::endl;
    if (src.cbegin()._node != nullptr) {
      this->head = _alloc.allocate(1);
      _alloc.construct(head, std::move(*src.cbegin()._node));
      auto p_dst = head;
      auto p_src = src.cbegin()._node;
      while (p_src->next != nullptr) {
        p_dst->next = _alloc.allocate(1);
        p_dst = p_dst->next;
        p_src = p_src->next;
        _alloc.construct(p_dst, std::move(*p_src));
      }
    }
  }

  // Destructor
  ~LinkedList() {
    std::cout << "LOG: LL dtor..." << std::endl;
    std::cout << "LOG: LL head (before destruct) = " << head << "..." << std::endl;
    auto current = head;
    while (current != nullptr) {
      auto p_rm = current;
      current = current->next;
      _alloc.destroy(p_rm);
      _alloc.deallocate(p_rm, 1);
    }
  }

  // @method
  // Append new Node in the end of the Linked List
  void push_back(const T& value) {
    // Allocate memory for a new Node
    auto new_node = _alloc.allocate(1);
    _alloc.construct(new_node);

    // Set parameters for a new Node
    new_node->data = value;
    new_node->next = nullptr;

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
  using Allocator = typename _A::template rebind< Node<T> >::other;
  Allocator _alloc;
};

#endif //ALLOCATOR_LINKED_LIST_H
