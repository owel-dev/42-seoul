/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 20:51:52 by ulee              #+#    #+#             */
/*   Updated: 2022/04/08 20:51:53 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <exception>
#include <iostream>
#include <memory>
#include <stdexcept>

#include "etc.hpp"
#include "reverse_iterator.hpp"

namespace ft
{

template<class T, class Allocator = std::allocator <T> >
class vector
{
  public:
  /*
   * 멤버 타입
   */
  typedef Allocator allocator_type;
  typedef T value_type;
  typedef long difference_type;
  typedef unsigned long size_type;

  typedef T *pointer;
  typedef const T *const_pointer;
  typedef T &reference;
  typedef const T &const_reference;

  typedef pointer iterator;
  typedef const_pointer const_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

  private:
  allocator_type _alloc;
  pointer _begin;
  pointer _end;
  pointer _end_cap;

  private:
  /*
   * 커스텀 함수
   */

  void vallocate(size_type n)
  {
    if (n > max_size())
      throw std::out_of_range("vector");
    _begin = _end = _alloc.allocate(n);
      _end_cap = _begin + n;
  }

  void vdeallocate()
  {
    if (_begin != nullptr) {
      this->clear();
      _alloc.deallocate(_begin, capacity());
      _begin = _end = _end_cap = nullptr;
    }
  }

  void construct_at_end(pointer new_end, const value_type &val)
  {
    for (; _end != new_end; ++_end) {
      _alloc.construct(_end, val);
    }
  }

  template<class Iterator1, class Iterator2>
  void construct_at_end(Iterator1 new_end, Iterator2 prev)
  {
    for (; _end != new_end; ++_end, ++prev) {
      _alloc.construct(_end, *prev);
    }
  }

  void destruct_at_end(pointer new_end)
  {
    while (_end != new_end)
      _alloc.destroy(--_end);
  }

  void append(size_type add_size, const value_type &val)
  {
    size_type exrta_cap = _end_cap - _end;
    if (exrta_cap >= add_size) {
      construct_at_end(_end + add_size, val);
    } else {
      this->reserve(recommand_cap(size() + add_size));
      construct_at_end(_end + add_size, val);
    }
  }

  size_type recommand_cap(size_type new_size)
  {
    const size_type max = max_size();
    if (new_size > max)
      throw std::out_of_range("vector");
    const size_type cap = capacity();
    if (cap >= max / 2)
      return max;
    return std::max(2 * cap, new_size);
  }

  public:
  /*
   * 기본 생성자, 소멸자 등
   */
  explicit vector(const allocator_type &alloc = allocator_type())
          : _alloc(alloc), _begin(nullptr), _end(nullptr), _end_cap(nullptr) {}

  explicit vector(size_type n, const value_type &val = value_type(),
                  const allocator_type &alloc = allocator_type())
          : _alloc(alloc), _begin(nullptr), _end(nullptr), _end_cap(nullptr)
  {
    if (n > 0) {
      vallocate(n);
      construct_at_end(_end + n, val);
    }
  }

  template<class InputIterator>
  vector(InputIterator first, InputIterator last,
         const allocator_type &alloc = allocator_type(),
         typename ft::enable_if<!ft::is_integral<InputIterator>::value,
                 InputIterator>::type * = nullptr)
          : _alloc(alloc)
  {
    difference_type n = std::distance(first, last);
    if (n > 0) {
      vallocate(n);
      construct_at_end(_end + n, first);
    }
  }

  vector(const vector &copy)
          : _alloc(copy._alloc), _begin(nullptr), _end(nullptr), _end_cap(nullptr)
  {
    size_type n = copy.size();
    if (n > 0) {
      vallocate(n);
      construct_at_end(_end + n, copy.begin());
    }
  }

  ~vector() { vdeallocate(); }

  vector &operator=(const vector &obj)
  {
    if (this != &obj) {
      this->assign(obj.begin(), obj.end());
    }
    return (*this);
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

  size_type max_size() const
  {
    return std::min<size_type>(_alloc.max_size(),
                               std::numeric_limits<difference_type>::max());
  }

  void resize(size_type n, const value_type &val = value_type())
  {
    size_type s = size();
    if (s < n) {
      append(n - s, val);
    } else if (s > n) {
      destruct_at_end(_begin + n);
    }
  }

  size_type capacity() const { return _end_cap - _begin; }

  bool empty() const { return size() == 0 ? true : false; }

  void reserve(size_type n)
  {
    if (capacity() < n) {
      pointer p_begin = _begin;
      size_type p_size = size();
      size_type p_cap = capacity();
      vallocate(n);
      construct_at_end(_begin + p_size, p_begin);
      _alloc.deallocate(p_begin, p_cap);
    }
  }

  // * Element access

  reference at(size_type n)
  {
    if (n >= size())
      throw std::out_of_range("vector");
    return _begin[n];
  }

  const_reference at(size_type n) const
  {
    if (n >= size())
      throw std::out_of_range("vector");
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
  void assign(size_type n, const value_type &val)
  {
    if (n <= capacity()) {
      std::uninitialized_fill_n(_begin, std::min(n, size()), val);
      _end = _begin + std::min(n, size());
      if (size() < n) {
        construct_at_end(_end + n - size(), val);
      } else
        destruct_at_end(_end);
    } else {
      vdeallocate();
      vallocate(n);
      construct_at_end(_end + n, val);
    }
  }

  template<class InputIterator>
  void assign(InputIterator first, InputIterator last,
              typename ft::enable_if<!ft::is_integral<InputIterator>::value,
                      InputIterator>::type * = nullptr)
  {
    clear();
    for (; first != last; ++first)
      push_back(*first);
  }

  void push_back(const value_type &val)
  {
    if (size() == capacity())
      this->reserve(recommand_cap(size() + 1));
    construct_at_end(_end + 1, val);
  }

  void pop_back() { destruct_at_end(_end - 1); }

  iterator insert(iterator position, const_reference val)
  {
    size_type dist = position - _begin;
    if (_end == _end_cap)
      this->reserve(recommand_cap(size() + 1));
    iterator new_position = _begin + dist;
    if (new_position != _end)
      std::memmove(new_position + 1, new_position,
                   sizeof(value_type) * (_end - new_position));
    _alloc.construct(new_position, val);
    ++_end;
    return position;
  }

  iterator insert(iterator position, size_type n, const_reference val)
  {
    size_type dist = position - _begin;
    if (_end_cap < _end + n)
      this->reserve(recommand_cap(size() + n));
    iterator new_position = _begin + dist;
    if (new_position == _end) {
      construct_at_end(_end + n, val);
    } else {
      std::memmove(new_position + n, new_position,
                   sizeof(value_type) * (_end - new_position));
      for (size_t i = 0; i < n; ++i) {
        _alloc.construct(new_position + i, val);
        ++_end;
      }
    }
    return new_position;
  }

  template<class InputIterator>
  iterator insert(iterator position, InputIterator first, InputIterator last,
                  typename ft::enable_if<!ft::is_integral<InputIterator>::value,
                          InputIterator>::type * = nullptr)
  {
    size_type dist = position - _begin;
    size_type n = std::distance(first, last);
    if (_end_cap < _end + n) {
      this->reserve(recommand_cap(size() + n));
    }
    pointer new_position = _begin + dist;
    if (new_position == _end)
      construct_at_end(_end + n, first);
    else {
      std::memmove(new_position + n, new_position,
                   sizeof(value_type) * (_end - new_position));
      for (size_type i = 0; i < n; ++i, ++first) {
        _alloc.construct(new_position + i, *first);
        ++_end;
      }
    }
    return new_position;
  }

  iterator erase(iterator position)
  {
    _alloc.destroy(position);
    size_type n = _end - _begin - 1;
    std::memcpy(position, position + 1, n * sizeof(value_type));
    --_end;
    return (position);
  }

  iterator erase(iterator first, iterator last)
  {
    for (iterator pos = first; pos != last; ++pos) {
      _alloc.destroy(pos);
    }
    size_type move_n = _end - last;
    size_type erase_n = last - first;
    std::memcpy(first, last, move_n * sizeof(value_type));
    std::memset(_end - erase_n, 0, erase_n);
    _end -= erase_n;

    return (first);
  }

  void swap(vector &x)
  {
    if (this == &x)
      return;
    std::swap(this->_begin, x._begin);
    std::swap(this->_end, x._end);
    std::swap(this->_end_cap, x._end_cap);
  }

  void clear() { destruct_at_end(_begin); }
};

template<class T, class Alloc>
bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
{
  return lhs.size() == rhs.size() &&
         ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template<class T, class Alloc>
bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
{
  return !(lhs == rhs);
}

template<class T, class Alloc>
bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
{
  return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                     rhs.end());
}

template<class T, class Alloc>
bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
{
  return rhs < lhs;
}

template<class T, class Alloc>
bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
{
  return !(rhs < lhs);
}

template<class T, class Alloc>
bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
{
  return !(lhs < rhs);
}

} // namespace ft

#endif
