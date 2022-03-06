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
  allocator_type __alloc_;
  pointer __begin_;
  pointer __end_;
  pointer __end_cap_;

 public:
  /*
   * 커스텀 함수
   */

  void __vallocate(size_type __n) {
    if (__n > max_size()) throw std::out_of_range("vector");
    __begin_ = __end_ = __alloc_.allocate(__n);
    __end_cap_ = __begin_ + __n;
  }

  void __vdeallocate() {
    if (__begin_ != nullptr) {
      clear();
      __alloc_.deallocate(__begin_, capacity());
      __begin_ = __end_ = __end_cap_ = nullptr;
    }
  }

  void __construct_at_end(pointer __new_end, const value_type& __val) {
    for (; __end_ != __new_end; ++__end_) {
      __alloc_.construct(__end_, __val);
    }
  }

  void __construct_at_end(pointer __new_end, pointer __prev) {
    for (; __end_ != __new_end; ++__end_, ++__prev) {
      __alloc_.construct(__end_, *__prev);
    }
  }

  void __destruct_at_end(pointer __new_end) {
    while (__end_ != __new_end) __alloc_.destroy(--__end_);
  }

  void __append(size_type __add_size, const value_type& __val) {
    size_type __exrta_cap = __end_cap_ - __end_;
    if (__exrta_cap < __add_size) {
      this->reserve(size() + __add_size);
    }
    pointer __new_end = __end_ + __add_size;
    __construct_at_end(__new_end, __val);
  }

  size_type __recommand_cap(size_type __new_size) {
    const size_type __max = max_size();
    if (__new_size > __max) throw std::out_of_range("vector");
    const size_type __cap = capacity();
    if (__cap >= __max / 2) return __max;
    return std::max(2 * __cap, __new_size);
  }

  /*
   * 기본 생성자, 소멸자 등
   */
  explicit vector(const allocator_type& __alloc = allocator_type())
      : __alloc_(__alloc),
        __begin_(nullptr),
        __end_(nullptr),
        __end_cap_(nullptr) {}

  explicit vector(size_type __n, const value_type& __val = value_type(),
                  const allocator_type& __alloc = allocator_type())
      : __alloc_(__alloc) {
    if (__n > 0) {
      __vallocate(__n);
      __construct_at_end(__end_ + __n, __val);
    }
  }

  // template <class InputIterator>
  // vector(InputIterator first, InputIterator last,
  //        const allocator_type& alloc = allocator_type(),
  //        typename ft::enable_if<!ft::is_integral<InputIterator>::value,
  //                               InputIterator>::type* = nullptr)
  //     : __alloc_(alloc) {
  //   size_type __n = distance(first, last);
  //   if (__n > 0) {
  //     set_alllocate(__n);
  //     for (pointer temp = _start; temp != __end_; ++temp, ++first) *temp =
  //     *first;
  //   }
  // }

  // vector(const vector& copy)
  //     : __alloc_(copy.__alloc_),
  //       _start(nullptr),
  //       __end_(nullptr),
  //       __end_cap_acity(nullptr) {
  //   for (pointer temp = _start; temp != __end_; ++temp, ++first) *temp =
  //   *first;
  // }

  // vector(const vector& x)
  //     : __alloc_(x.__alloc_),
  //       _start(u_nullptr),
  //       __end_(u_nullptr),
  //       __end_cap_acity(u_nullptr) {
  //   this->insert(this->begin(), x.begin(), x.end());
  // }
  // ~vector() {
  //   for (iterator it = begin(); it != end(); ++it) __alloc_.destroy(&(*it));
  //   __alloc_.deallocate(_start, _size);
  // };
  // vector& operator=(const vector& obj);
  // allocator_type get_allocator() const;

  /*
   * 반복자
   */
  iterator begin() { return __begin_; }
  const_iterator begin() const { return __begin_; }
  iterator end() { return __end_; }
  const_iterator end() const { return __end_; }
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

  size_type size() const { return __end_ - __begin_; }
  size_type max_size() const { return allocator_type().max_size(); }
  void resize(size_type __n, const value_type& __val = value_type()) {
    size_type __s = size();
    if (__s < __n) {
      __append(__n - __s, __val);
    } else if (__s > __n) {
      __destruct_at_end(__begin_ + __n);
    }
  }

  size_type capacity() const { return __end_cap_ - __begin_; }
  bool empty() const { return size() == 0 ? true : false; }
  void reserve(size_type __n) {
    pointer __p_begin = __begin_;
    size_type __p_size = size();
    size_type __p_cap = capacity();
    __vallocate(__n);
    __construct_at_end(__begin_ + __p_size, __p_begin);
    __alloc_.deallocate(__p_begin, __p_cap);
  }

  /*
   * Element access
   */
  reference at(size_type __n) {
    if (__n >= size()) throw std::out_of_range("vector");
    return __begin_[__n];
  }
  const_reference at(size_type __n) const {
    if (__n >= size()) throw std::out_of_range("vector");
    return __begin_[__n];
  }
  reference operator[](size_type __n) { return __begin_[__n]; };
  const_reference operator[](size_type __n) const { return __begin_[__n]; }
  reference front() { return *__begin_; }
  const_reference front() const { return *__begin_; }
  reference back() { return *(__end_ - 1); }
  const_reference back() const { return *(__end_ - 1); }

  /*
   * Modifiers
   */
  void assign(size_type __n, const value_type& __val) {
    if (__n <= capacity()) {
      size_type __s = size();
      std::fill_n(__begin_, std::min(__n, __s), __val);
      if (__n > __s) {
        size_type __add_size = __n - __s;
        __construct_at_end(__end_ + __add_size, __val);
      } else
        __destruct_at_end(__begin_ + __n);
    } else {
      __vdeallocate();
      __vallocate(__recommand_cap(__n));
      __construct_at_end(__end_ + __n, __val);
    }
  }

  template <class InputIterator>
  void assign(InputIterator __first, InputIterator __last,
              typename ft::enable_if<!ft::is_integral<InputIterator>::value,
                                     InputIterator>::type* = nullptr) {
    clear();
    for (; __first != __last; ++__first) push_back(*__first);
  }

  void push_back(const value_type& __val) {
    if (__end_ == __end_cap_) {
      size_type __new_size = __recommand_cap(size() + 1);
      this->reserve(__new_size);
    }
    __construct_at_end(__end_ + 1, __val);
  }

  void pop_back() { __destruct_at_end(__end_ - 1); }

  iterator insert(iterator position, const value_type& __val) {
    size_type __d = position - __begin_;
    if (__end_ == __end_cap_) {
      this->reserve(__recommand_cap(1));
    }
    pointer __pos = __begin_ + __d;
    if (__pos == __end_)
      __alloc_.construct(__end_, __val);
    else {
      for (pointer __old_end = __end_; __old_end != __pos; --__old_end)
        __alloc_.construct(__old_end, *(__old_end - 1));
      ++__end_;
      __alloc_.construct(__pos, __val);
    }
    return __pos;
  }

  template <class InputIterator>
  iterator insert(InputIterator __position, size_type __n,
                  const value_type& __val) {
    size_type __d = __position - __begin_;
    if (__end_cap_ < __end_ + __n) {
      this->reserve(__recommand_cap(capacity() + __d));
    }
    pointer __pos = __begin_ + __d;
    if (__pos == __end_)
      __construct_at_end(__end_ + __n, __val);
    else {
      pointer __back = __end_ + __n - 1;
      for (pointer __old_end = __end_; __old_end != __pos;
           --__old_end, --__back) {
        __alloc_.construct(__back, *(__old_end - 1));
      }
      for (size_t i = 0; i < __n; ++i, ++__pos, ++__end_)
        __alloc_.construct(__pos, __val);
    }
    return __pos - __n;
  }
  template <class InputIterator>
  iterator insert(iterator __position, InputIterator __first,
                  InputIterator __last,
                  typename ft::enable_if<!ft::is_integral<InputIterator>::value,
                                         InputIterator>::type* = nullptr) {
    size_type __off = __position - __begin_;
    size_type __n = __last - __first;
    if (__end_cap_ < __end_ + __n) {
      this->reserve(__recommand_cap(capacity() + __off));
    }
    pointer __pos = __begin_ + __off;
    if (__pos == __end_)
      __construct_at_end(__end_ + __n, *__first);
    else {
      pointer __back = __end_ + __n - 1;
      for (pointer __old_end = __end_; __old_end != __pos;
           --__old_end, --__back) {
        __alloc_.construct(__back, *(__old_end - 1));
      }
      for (size_t i = 0; i < __n; ++i, ++__pos, ++__end_, ++__first)
        __alloc_.construct(__pos, *__first);
    }
    return __pos - __n;
  }

  // iterator erase(iterator position) {}

  // iterator erase(iterator first, iterator last) {}
  void swap(vector& x) {}
  void clear() { __destruct_at_end(__begin_); }
};

}  // namespace ft

#endif
