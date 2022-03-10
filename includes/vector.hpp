#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <exception>
#include <iostream>
#include <memory>
#include <stdexcept>

#include "etc.hpp"
#include "reverse_iterator.hpp"

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
  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

 private:
  allocator_type _alloc;
  pointer _begin;
  pointer _end;
  pointer _end_cap;

 public:
  /*
   * 커스텀 함수
   */

  void vallocate(size_type n) {
    if (n > max_size()) throw std::out_of_range("vector");
    _begin = _end = _alloc.allocate(n);
    _end_cap = _begin + n;
  }

  void vdeallocate() {
    if (_begin != nullptr) {
      this->clear();
      _alloc.deallocate(_begin, capacity());
      _begin = _end = _end_cap = nullptr;
    }
  }

  void construct_at_end(pointer new_end, const value_type& val) {
    for (; _end != new_end; ++_end) {
      _alloc.construct(_end, val);
    }
  }

  void construct_at_end(pointer new_end, pointer prev) {
    for (; _end != new_end; ++_end, ++prev) {
      _alloc.construct(_end, *prev);
    }
  }

  void destruct_at_end(pointer new_end) {
    while (_end != new_end) _alloc.destroy(--_end);
  }

  void append(size_type add_size, const value_type& val) {
    size_type exrta_cap = _end_cap - _end;
    if (exrta_cap < add_size) {
      this->reserve(size() + add_size);
    }
    pointer new_end = _end + add_size;
    construct_at_end(new_end, val);
  }

  size_type recommand_cap(size_type new_size) {
    const size_type max = max_size();
    if (new_size > max) throw std::out_of_range("vector");
    const size_type cap = capacity();
    if (cap >= max / 2) return max;
    return std::max(2 * cap, new_size);
  }

  /*
   * 기본 생성자, 소멸자 등
   */
  explicit vector(const allocator_type& alloc = allocator_type())
      : _alloc(alloc), _begin(nullptr), _end(nullptr), _end_cap(nullptr) {}

  explicit vector(size_type n, const value_type& val = value_type(),
                  const allocator_type& alloc = allocator_type())
      : _alloc(alloc), _begin(nullptr), _end(nullptr), _end_cap(nullptr) {
    if (n > 0) {
      vallocate(n);
      construct_at_end(_end + n, val);
    }
  }

  template <class InputIterator>
  vector(InputIterator first, InputIterator last,
         const allocator_type& alloc = allocator_type(),
         typename ft::enable_if<!ft::is_integral<InputIterator>::value,
                                InputIterator>::type* = nullptr)
      : _alloc(alloc) {
    size_type n = last - first;
    if (n > 0) {
      vallocate(n);
      construct_at_end(_end + n, first);
    }
  }

  vector(const vector& copy)
      : _alloc(copy._alloc), _begin(nullptr), _end(nullptr), _end_cap(nullptr) {
    size_type n = copy.size();
    if (n > 0) {
      vallocate(n);
      construct_at_end(_end + n, copy.begin());
    }
  }

  ~vector() { vdeallocate(); }
  vector& operator=(const vector& obj) {
    if (this != &obj) {
      this->assign(obj.begin(), obj.end());
    }
  }
  allocator_type get_allocator() const { return this->_alloc(); }

  /*
   * 반복자
   */
  iterator begin() { return _begin; }
  const_iterator begin() const { return _begin; }
  iterator end() { return _end; }
  const_iterator end() const { return _end; }
  reverse_iterator rbegin() { return reverse_iterator(_end); }
  const_reverse_iterator rbegin() const { return reverse_iterator(_end); }
  reverse_iterator rend() { return reverse_iterator(_begin); }
  const_reverse_iterator rend() const { return reverse_iterator(_begin); }

  /*
   * Capacity
   */

  size_type size() const { return _end - _begin; }
  size_type max_size() const { return allocator_type().max_size(); }
  void resize(size_type n, const value_type& val = value_type()) {
    size_type s = size();
    if (s < n) {
      append(n - s, val);
    } else if (s > n) {
      destruct_at_end(_begin + n);
    }
  }

  size_type capacity() const { return _end_cap - _begin; }
  bool empty() const { return size() == 0 ? true : false; }
  void reserve(size_type n) {
    pointer p_begin = _begin;
    size_type p_size = size();
    size_type p_cap = capacity();
    vallocate(n);
    construct_at_end(_begin + p_size, p_begin);
    _alloc.deallocate(p_begin, p_cap);
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
  void assign(size_type n, const value_type& val) {
    if (n <= capacity()) {
      size_type s = size();
      std::fill_n(_begin, std::min(n, s), val);
      if (n > s) {
        size_type add_size = n - s;
        construct_at_end(_end + add_size, val);
      } else
        destruct_at_end(_begin + n);
    } else {
      vdeallocate();
      vallocate(recommand_cap(n));
      construct_at_end(_end + n, val);
    }
  }

  template <class InputIterator>
  void assign(InputIterator first, InputIterator last,
              typename ft::enable_if<!ft::is_integral<InputIterator>::value,
                                     InputIterator>::type* = nullptr) {
    clear();
    for (; first != last; ++first) push_back(*first);
  }

  void push_back(const value_type& val) {
    if (_end == _end_cap) {
      size_type new_size = recommand_cap(size() + 1);
      this->reserve(new_size);
    }
    construct_at_end(_end + 1, val);
  }

  void pop_back() { destruct_at_end(_end - 1); }

  iterator insert(iterator position, const value_type& val) {
    size_type d = position - _begin;
    if (_end == _end_cap) {
      this->reserve(recommand_cap(1));
    }
    pointer pos = _begin + d;
    if (pos == _end)
      _alloc.construct(_end, val);
    else {
      for (pointer old_end = _end; old_end != pos; --old_end)
        _alloc.construct(old_end, *(old_end - 1));
      ++_end;
      _alloc.construct(pos, val);
    }
    return pos;
  }

  template <class InputIterator>
  iterator insert(InputIterator position, size_type n, const value_type& val) {
    size_type d = position - _begin;
    if (_end_cap < _end + n) {
      this->reserve(recommand_cap(capacity() + d));
    }
    pointer pos = _begin + d;
    if (pos == _end)
      construct_at_end(_end + n, val);
    else {
      pointer back = _end + n - 1;
      for (pointer old_end = _end; old_end != pos; --old_end, --back) {
        _alloc.construct(back, *(old_end - 1));
      }
      for (size_t i = 0; i < n; ++i, ++pos, ++_end) _alloc.construct(pos, val);
    }
    return pos - n;
  }

  template <class InputIterator>
  iterator insert(iterator position, InputIterator first, InputIterator last,
                  typename ft::enable_if<!ft::is_integral<InputIterator>::value,
                                         InputIterator>::type* = nullptr) {
    size_type off = position - _begin;
    size_type n = last - first;
    if (_end_cap < _end + n) {
      this->reserve(recommand_cap(capacity() + off));
    }
    pointer pos = _begin + off;
    if (pos == _end)
      construct_at_end(_end + n, *first);
    else {
      pointer back = _end + n - 1;
      for (pointer old_end = _end; old_end != pos; --old_end, --back) {
        _alloc.construct(back, *(old_end - 1));
      }
      for (size_t i = 0; i < n; ++i, ++pos, ++_end, ++first)
        _alloc.construct(pos, *first);
    }
    return pos - n;
  }

  iterator erase(iterator position) {
    _alloc.destroy(position);
    size_type n = _end - _begin - 1;
    std::memcpy(position, position + 1, n * sizeof(value_type));
    *(_end - 1) = 0;
    --_end;
    return (position);
  }

  iterator erase(iterator first, iterator last) {
    for (iterator pos = first; pos != last; ++pos) {
      _alloc.destroy(pos);
    }
    size_type move_n = _end - last;
    size_type erase_n = last - first;
    std::memcpy(first, last, move_n * sizeof(value_type));
    std::memset(_end - erase_n, 0, erase_n);
    _end -= erase_n;
  }
  void swap(vector& x) {
    if (*this == x) return;
    std::swap(this->_begin, x._begin);
    std::swap(this->_end, x._end);
    std::swap(this->_end_cap, x._end_cap);
  }
  void clear() { destruct_at_end(_begin); }
};

template <class T, class Alloc>
bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
  return lhs.size() == rhs.size() &&
         std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <class T, class Alloc>
bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
  return !(lhs == rhs);
}

template <class T, class Alloc>
bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
  return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                      rhs.end());
}

template <class T, class Alloc>
bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
  return rhs < lhs;
}

template <class T, class Alloc>
bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
  return !(rhs < lhs);
}

template <class T, class Alloc>
bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
  return !(lhs < rhs);
}

}  // namespace ft

#endif
