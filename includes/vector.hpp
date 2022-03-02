#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <exception>
#include <iostream>
#include <memory>
#include <stdexcept>

#include "utils.hpp"
#include "vector_iterator.hpp"

namespace ft {

template <class T, class Allocator = std::allocator<T> >
class vector {
 public:
  /*
   * 멤버 타입
   */
  typedef Allocator allocator_type;
  typedef T value_type;
  typedef long difference_type;
  typedef unsigned long size_type;

  typedef T* pointer;
  typedef const T* const_pointer;
  typedef T& reference;
  typedef const T& const_reference;

  typedef ft::vector_iterator<value_type> iterator;
  typedef ft::vector_iterator<const value_type> const_iterator;
  // typedef ft::vector_iterator<const value_type> iterator;
  // typedef typename allocator_type::size_type size_type;
  // typedef Allocator::const_pointer const_pointer;
  // typedef ft::reverse_iterator<iterator> reverse_iterator;
  // typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

 private:
  allocator_type _alloc;
  pointer _begin;
  pointer _end;
  pointer _end_cap;

 public:
  /*
   * 커스텀 함수
   */
  void re_allocate(size_type n) {
    if (n > max_size()) throw std::out_of_range("vector");
    _begin = _end = _alloc.allocate(n);
    _end_cap = _begin + n;
  }

  void construct_at_end(pointer _new_end, const value_type& val) {
    for (; _end != _new_end; ++_end) {
      _alloc.construct(_end, val);
    }
  }

  void construct_at_end(pointer _new_end, pointer val) {
    for (; _end != _new_end; ++_end, ++val) {
      _alloc.construct(_end, *val);
    }
  }

  size_type new_capacity(size_type size) {
    if (size == 1) return (size);
    const size_type max = max_size();
    if (size > max) throw std::out_of_range("vector");
    const size_type cap = capacity();
    if (cap >= max / 2) return max;
    return cap * 2;
  }

  /*
   * 기본 생성자, 소멸자 등
   */
  explicit vector(const allocator_type& alloc = allocator_type())
      : _alloc(alloc), _begin(nullptr), _end(nullptr), _end_cap(nullptr) {}

  explicit vector(size_type n, const value_type& val = value_type(),
                  const allocator_type& alloc = allocator_type())
      : _alloc(alloc) {
    if (n > 0) {
      re_allocate(n);
      construct_at_end(_end + n, val);
    }
  }

  // template <class InputIterator>
  // vector(InputIterator first, InputIterator last,
  //        const allocator_type& alloc = allocator_type(),
  //        typename ft::enable_if<!ft::is_integral<InputIterator>::value,
  //                               InputIterator>::type* = nullptr)
  //     : _alloc(alloc) {
  //   size_type n = distance(first, last);
  //   if (n > 0) {
  //     set_alllocate(n);
  //     for (pointer temp = _start; temp != _end; ++temp, ++first) *temp =
  //     *first;
  //   }
  // }

  // vector(const vector& copy)
  //     : _alloc(copy._alloc),
  //       _start(nullptr),
  //       _end(nullptr),
  //       _end_capacity(nullptr) {
  //   for (pointer temp = _start; temp != _end; ++temp, ++first) *temp =
  //   *first;
  // }

  // vector(const vector& x)
  //     : _alloc(x._alloc),
  //       _start(u_nullptr),
  //       _end(u_nullptr),
  //       _end_capacity(u_nullptr) {
  //   this->insert(this->begin(), x.begin(), x.end());
  // }
  // ~vector() {
  //   for (iterator it = begin(); it != end(); ++it) _alloc.destroy(&(*it));
  //   _alloc.deallocate(_start, _size);
  // };
  // vector& operator=(const vector& obj);
  // allocator_type get_allocator() const;

  /*
   * 반복자
   */
  iterator begin() { return iterator(_begin); }
  // const_iterator begin() const { return const_itrator(_vector); }
  iterator end() const { return iterator(_end); }
  // const_iterator end() const { return const_iterator(_vector + _size); }
  // reverse_iterator rbegin() { return reverse_iterator(_vector + _size - 1); }
  // const_reverse_iterator rbegin() const {
  //   return const_reverse_iterator(_vector + _size - 1);
  // }
  // reverse_iterator rend() { return reverse_iterator(_vector - 1); }
  // const_reverse_iterator rend() const {
  //   return const_reverse_iterator(_vector - 1);
  // }

  /*
   * Capacity
   */
  size_type size() const { return _end - _begin; }
  size_type max_size() const { return allocator_type().max_size(); }
  // void resize(size_type n) { if }
  size_type capacity() const { return _end_cap - _begin; }
  // bool empty() const {}
  void reserve(size_type n) {
    size_type prev_size = size();
    pointer prev_begin = _begin;
    re_allocate(n);
    // for (size_t i = 0; i < prev_size; ++i, ++_end)
    //   _alloc.construct(_end, prev_begin[i]);
    construct_at_end(_end + prev_size, prev_begin);
    _alloc.deallocate(prev_begin, prev_size);
  }

  /*
   * Element access
   */
  // reference at(size_type n) {
  //   if (n >= _size) throw std::out_of_range("vector");
  //   return _start[n];
  // }
  // reference operator[](size_type n);
  // const_reference operator[](size_type n) const;
  // const_reference at(size_type n) const;
  // reference front() { return *_start; }
  // const_reference front() const { return *_start; }
  // reference back() { return *(_end - 1); }
  // const_reference back() const { return *(_end - 1); }

  /*
   * Modifiers
   */
  // template <class InputIterator>
  // void assign(InputIterator first, InputIterator last) {}
  // void assign(size_type n, const value& val) {}

  void push_back(const value_type& val) {
    if (_end == _end_cap) {
      size_type new_size = new_capacity(size() + 1);
      reserve(new_size);
    }
    _alloc.construct(_end, val);
    ++_end;
  }

  // void pop_back() {
  //   if (_size) {
  //     _alloc.destroy(_end - 1);
  //   }
  //   --_size;
  //   --_end;
  // }
  // iterator insert(iterator position, const value_type& val) {}
  // void insert(iterator position, size_type n, const value_type& val) {}
  // template <class InputIterator>
  // void insert(interator position, InputIterator first, InputIterator last) {}
  // iterator erase(iterator position) {}
  // iterator erase(iterator first, iterator last) {}
  // void swap(vector& x) {}
  // void clear();
};

}  // namespace ft

#endif
