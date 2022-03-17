#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <memory>
#define NC "\e[0m"
#define RED_C "\e[31m"
#define BLACK_C "\e[30m \e[1m"
#define BLUE "\e[36m"

namespace ft {

enum Color { RED, BLACK, DOUBLE_BLACK };

template <class T>
struct Node {
  T data;
  int color;
  Node *left, *right, *parent;

  Node() {
    this->data = 0;
    this->color = BLACK;
    this->left = this->right = this->parent = nullptr;
  }

  explicit Node(int data, Node* nil) {
    this->data = data;
    this->color = RED;
    this->parent = nullptr;
    this->left = this->right = nil;
  }
};

template <class T1, class T2>
class pair {
 public:
  typedef T1 first_type;
  typedef T2 second_type;

  first_type first;
  first_type second;

  pair() : first(), second() {}

  template <class U, class V>
  pair(const pair<U, V>& pr) : first(pr.first), second(pr.second) {}

  pair(const first_type& a, const second_type& b) : first(a), second(b) {}

  pair& operator=(const pair& pr) {
    if (*this == pr) return (*this);
    this->first = pr.first;
    this->second = pr.second;
    return (*this);
  }
};

template <class T1, class T2>
bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
  return lhs.first == rhs.first && lhs.second == rhs.second;
}

template <class T1, class T2>
bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
  return !(lhs == rhs);
}

template <class T1, class T2>
bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
  return lhs.first < rhs.first ||
         (!(rhs.first < lhs.first) && lhs.second < rhs.second);
}

template <class T1, class T2>
bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
  return !(rhs < lhs);
}

template <class T1, class T2>
bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
  return rhs < lhs;
}

template <class T1, class T2>
bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
  !(lhs < rhs);
}

template <class Iterator>
struct iterator_traits {
  typedef typename Iterator::difference_type difference_type;
  typedef typename Iterator::value_type value_type;
  typedef typename Iterator::pointer pointer;
  typedef typename Iterator::reference reference;
  typedef typename Iterator::iterator_category iterator_category;
};

template <class T>
struct iterator_traits<T*> {
  typedef ptrdiff_t difference_type;
  typedef T value_type;
  typedef T* pointer;
  typedef T& reference;
  typedef std::random_access_iterator_tag iterator_category;
};

template <class T>
class iterator_traits<const T*> {
  typedef ptrdiff_t difference_type;

  typedef T value_type;
  typedef const T* pointer;
  typedef const T& reference;
  typedef std::random_access_iterator_tag iterator_category;
};

template <bool B, class T = void>
struct enable_if {};
template <class T>
struct enable_if<true, T> {
  typedef T type;
};

/* ----------------------------------------------- *
 *                   is_integral                   *
 * ----------------------------------------------- */
template <typename T>
struct is_integral {
  static const bool value = false;
};

template <>
struct is_integral<bool> {
  static const bool value = true;
};

template <>
struct is_integral<char> {
  static const bool value = true;
};

template <>
struct is_integral<short> {
  static const bool value = true;
};

template <>
struct is_integral<int> {
  static const bool value = true;
};

template <>
struct is_integral<long> {
  static const bool value = true;
};

template <>
struct is_integral<long long> {
  static const bool value = true;
};

template <>
struct is_integral<unsigned char> {
  static const bool value = true;
};

template <>
struct is_integral<unsigned short> {
  static const bool value = true;
};

template <>
struct is_integral<unsigned int> {
  static const bool value = true;
};

template <>
struct is_integral<unsigned long> {
  static const bool value = true;
};

template <>
struct is_integral<unsigned long long> {
  static const bool value = true;
};
class random_access_iterator_tag {};

}  // namespace ft

#endif