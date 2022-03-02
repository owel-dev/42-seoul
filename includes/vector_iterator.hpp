#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP
#include "iterator"

namespace ft {
template <typename T>
class vector_iterator {
  typedef T* pointer;
  typedef T value_type;

 private:
  pointer _it;

 public:
  vector_iterator(pointer p = nullptr) : _it(p) {}

  bool operator!=(const vector_iterator& right) { return _it != right._it; }
  value_type& operator*() { return *_it; }
  pointer get_it() { return _it; }
  vector_iterator& operator++() {
    ++_it;
    return *this;
  }
};

}  // namespace ft

// #ifndef RANDOM_ACCESS_ITERATOR_HPP
// #define RANDOM_ACCESS_ITERATOR_HPP
// #include <iostream>
// #include <memory>

// namespace ft {
// template <typename T>
// class random_access_iterator {
//   typedef long int difference_type;
//   typedef unsigned long int size_type;
//   typedef T value_type;
//   typedef T* pointer;
//   typedef T& reference;
//   typedef std::random_access_iterator_tag iterator_category;

//  public:
//   random_access_iterator(pointer arg = nullptr) : current(arg) {}

//   random_access_iterator(const random_access_iterator& copy)
//       : current(copy.current) {}

//   random_access_iterator& operator=(const random_access_iterator& assign) {
//     if (this != &assign) current = assign.current;
//     return (*this);
//   }

//   virtual ~random_access_iterator() {}

//   pointer base() const { return (current); }

//   reference operator*() const { return (*current); }
//   pointer operator->() const { return (current); }

//   random_access_iterator& operator++() {
//     ++current;
//     return (*this);
//   }

//   random_access_iterator operator++(int) {
//     random_access_iterator temp(*this);
//     ++current;
//     return (temp);
//   }

//   random_access_iterator& operator--() {
//     --current;
//     return (*this);
//   }

//   random_access_iterator operator--(int) {
//     random_access_iterator temp(*this);
//     --current;
//     return (temp);
//   }

//   bool operator==(const random_access_iterator& robj) const {
//     return (current == robj.current);
//   }

//   bool operator!=(const random_access_iterator& robj) const {
//     return (current != robj.current);
//   }

//   bool operator<(const random_access_iterator& robj) const {
//     return (current < robj.current);
//   }

//   bool operator<=(const random_access_iterator& robj) const {
//     return (current <= robj.current);
//   }

//   bool operator>(const random_access_iterator& robj) const {
//     return (current > robj.current);
//   }

//   bool operator>=(const random_access_iterator& robj) const {
//     return (current >= robj.current);
//   }

//   random_access_iterator operator+(int n) const {
//     random_access_iterator temp(*this);
//     temp.current += n;
//     return (temp);
//   }

//   random_access_iterator operator-(int n) {
//     random_access_iterator temp(*this);
//     temp.current -= n;
//     return (temp);
//   }

//   random_access_iterator& operator+=(int n) {
//     current += n;
//     return (*this);
//   }

//   random_access_iterator& operator-=(int n) {
//     current -= n;
//     return (*this);
//   }

//   reference operator[](int n) { return (*(operator+(n))); }

//  private:
//   pointer current;
// }  // namespace ft

#endif
