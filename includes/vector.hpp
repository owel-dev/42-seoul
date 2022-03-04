#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <exception>
#include <iostream>
#include <memory>
#include <stdexcept>

// #include "split_buffer.hpp"
#include "utils.hpp"
// #include "vector_iterator.hpp"

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

  typedef pointer iterator;
  typedef const pointer const_iterator;
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

  void init_allocate(size_type n) {
    if (n > max_size()) throw std::out_of_range("vector");
    _begin = _end = _alloc.allocate(n);
    _end_cap = _begin + n;
  }

  void construct_at_end(pointer _new_end, const value_type& val) {
    for (; _end != _new_end; ++_end) {
      _alloc.construct(_end, val);
    }
  }

  void construct_at_end(pointer _new_end, pointer prev) {
    for (; _end != _new_end; ++_end, ++prev) {
      _alloc.construct(_end, *prev);
    }
  }

  void destruct_at_end(pointer new_end) {
    while (_end != new_end) _alloc.destroy(--_end);
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
      init_allocate(n);
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
  iterator begin() { return _begin; }
  const_iterator begin() const { return _begin; }
  iterator end() { return _end; }
  const_iterator end() const { return _end; }
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

  void append(size_type additional_size, const value_type& val) {
    size_type exrta_capacity = _end_cap - _end;
    if (exrta_capacity < additional_size) {
      size_type current_size = size();
      reserve(current_size + additional_size);
    }
    pointer new_end = _end + additional_size;
    construct_at_end(new_end, val);
  }

  size_type size() const { return _end - _begin; }
  size_type max_size() const { return allocator_type().max_size(); }
  void resize(size_type new_size, const value_type& val = value_type()) {
    size_type current_size = size();
    if (current_size < new_size) {
      append(new_size - current_size, val);
    } else if (current_size > new_size) {
      destruct_at_end(_begin + new_size);
    }
  }

  size_type capacity() const { return _end_cap - _begin; }
  bool empty() const { return size() == 0 ? true : false; }
  void reserve(size_type n) {
    pointer prev_begin = _begin;
    size_type prev_size = size();
    size_type prev_capacity = capacity();
    init_allocate(n);
    construct_at_end(_begin + prev_size, prev_begin);
    _alloc.deallocate(prev_begin, prev_capacity);
  }

  /*
   * Element access
   */
  reference at(size_type n) {
    if (n >= size()) throw std::out_of_range("vector");
    return _begin[n];
  }
  const_reference at(size_type n) const {
    if (n >= size()) throw std::out_of_range("vector");
    return _begin[n];
  }
  reference operator[](size_type n) { return _begin[n]; };
  const_reference operator[](size_type n) const { return _begin[n]; }
  reference front() { return *_begin; }
  const_reference front() const { return *_begin; }
  reference back() { return *(_end - 1); }
  const_reference back() const { return *(_end - 1); }

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
