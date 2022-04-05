#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <memory>
#include <utility>
#include <iomanip>
#include <algorithm>

#define NC "\e[0m"
#define RED_C "\e[31m"
#define BLACK_C "\e[30m \e[1m"
#define BLUE "\e[36m"

namespace ft
{

// * equal
template<class InputIterator1, class InputIterator2>
bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
{
  for (; first1 != last1; ++first1, ++first2)
    if (*first1 != *first2)
      return false;
  return true;
}

// * lexicographical_compare
template<class InputIterator1, class InputIterator2>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                             InputIterator2 first2, InputIterator2 last2)
{
  for (; first2 != last2; ++first1, ++first2)
  {
    if (first1 == last1 || *first1 < *first2)
      return true;
    if (*first2 < *first1)
      return false;
  }
  return false;
}


// * binary_function

template<class T1, class T2, class Result>
struct binary_function
{
  typedef T1 first_argument_type;
  typedef T2 second_argument_type;
  typedef Result result_type;
};

// * rb_node

template<class T, class Alloc = std::allocator<T> >
class rb_node
{
  public:
  typedef T value_type;
  typedef rb_node *node_pointer;

  value_type data;
  bool is_black;
  node_pointer left, right, parent;

  public:
  explicit rb_node()
  {
    this->is_black = true;
    this->left = this->right = this->parent = nullptr;
  }

  explicit rb_node(value_type data)
  {
    this->data = data;
    this->is_black = false;
    this->left = this->right = this->parent = nullptr;
  }
};

// * pair

template<class T1, class T2>
class pair
{
  public:
  typedef T1 first_type;
  typedef T2 second_type;

  first_type first;
  second_type second;

  pair() : first(), second() {}

  template<class U, class V>
  pair(const pair<U, V> &pr) : first(pr.first), second(pr.second) {}

  pair(const first_type &a, const second_type &b) : first(a), second(b) {}

  pair &operator=(const pair &pr)
  {
    this->first = pr.first;
    this->second = pr.second;
    return (*this);
  }
};

template<class T1, class T2>
pair<T1, T2> make_pair(T1 x, T2 y)
{
  return (pair<T1, T2>(x, y));
}

template<class T1, class T2>
std::ostream &operator<<(std::ostream &os, const ft::pair<T1, T2> &x)
{
  os << x.first;
  return os;
}

template<class T1, class T2>
bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
{
  return lhs.first == rhs.first && lhs.second == rhs.second;
}

template<class T1, class T2>
bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
{
  return !(lhs == rhs);
}

template<class T1, class T2>
bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
{
  return (lhs.first < rhs.first) ||
         (!(rhs.first < lhs.first) && (lhs.second < rhs.second));
}

template<class T1, class T2>
bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
{
  return !(rhs < lhs);
}

template<class T1, class T2>
bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
{
  return rhs < lhs;
}

template<class T1, class T2>
bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
{
  !(lhs < rhs);
}

// * iterator_traits

template<class Iterator>
struct iterator_traits
{
  typedef typename Iterator::difference_type difference_type;
  typedef typename Iterator::value_type value_type;
  typedef typename Iterator::pointer pointer;
  typedef typename Iterator::reference reference;
  typedef typename Iterator::iterator_category iterator_category;
};

template<class T>
struct iterator_traits<T *>
{
  typedef ptrdiff_t difference_type;
  typedef T value_type;
  typedef T *pointer;
  typedef T &reference;
  typedef std::random_access_iterator_tag iterator_category;
};

template<class T>
struct iterator_traits<const T *>
{
  typedef ptrdiff_t difference_type;
  typedef T value_type;
  typedef const T *pointer;
  typedef const T &reference;
  typedef std::random_access_iterator_tag iterator_category;
};

// * enable_if

template<bool B, class T = void>
struct enable_if
{
};
template<class T>
struct enable_if<true, T>
{
  typedef T type;
};

// * is_integral

template<typename T>
struct is_integral
{
  static const bool value = false;
};

template<>
struct is_integral<bool>
{
  static const bool value = true;
};

template<>
struct is_integral<char>
{
  static const bool value = true;
};

template<>
struct is_integral<short>
{
  static const bool value = true;
};

template<>
struct is_integral<int>
{
  static const bool value = true;
};

template<>
struct is_integral<long>
{
  static const bool value = true;
};

template<>
struct is_integral<long long>
{
  static const bool value = true;
};

template<>
struct is_integral<unsigned char>
{
  static const bool value = true;
};

template<>
struct is_integral<unsigned short>
{
  static const bool value = true;
};

template<>
struct is_integral<unsigned int>
{
  static const bool value = true;
};

template<>
struct is_integral<unsigned long>
{
  static const bool value = true;
};

template<>
struct is_integral<unsigned long long>
{
  static const bool value = true;
};

class random_access_iterator_tag
{
};

} // namespace ft

#endif