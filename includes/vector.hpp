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
  // typedef ft::reverse_iterator<iterator> reverse_iterator;
  // typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

 private:
  allocator_type alloc_;
  pointer begin_;
  pointer end_;
  pointer end_cap_;

 public:
  /*
   * 커스텀 함수
   */

  void vallocate(size_type n) {
    if (n > max_size()) throw std::out_of_range("vector");
    begin_ = end_ = alloc_.allocate(n);
    end_cap_ = begin_ + n;
  }

  void vdeallocate() {
    if (begin_ != nullptr) {
      this->clear();
      alloc_.deallocate(begin_, capacity());
      begin_ = end_ = end_cap_ = nullptr;
    }
  }

  void construct_at_end(pointer new_end, const value_type& val) {
    for (; end_ != new_end; ++end_) {
      alloc_.construct(end_, val);
    }
  }

  void construct_at_end(pointer new_end, pointer prev) {
    for (; end_ != new_end; ++end_, ++prev) {
      alloc_.construct(end_, *prev);
    }
  }

  void destruct_at_end(pointer new_end) {
    while (end_ != new_end) alloc_.destroy(--end_);
  }

  void append(size_type add_size, const value_type& val) {
    size_type exrta_cap = end_cap_ - end_;
    if (exrta_cap < add_size) {
      this->reserve(size() + add_size);
    }
    pointer new_end = end_ + add_size;
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
      : alloc_(alloc), begin_(nullptr), end_(nullptr), end_cap_(nullptr) {}

  explicit vector(size_type n, const value_type& val = value_type(),
                  const allocator_type& alloc = allocator_type())
      : alloc_(alloc) {
    if (n > 0) {
      vallocate(n);
      construct_at_end(end_ + n, val);
    }
  }

  template <class InputIterator>
  vector(InputIterator first, InputIterator last,
         const allocator_type& alloc = allocator_type(),
         typename ft::enable_if<!ft::is_integral<InputIterator>::value,
                                InputIterator>::type* = nullptr)
      : alloc_(alloc) {
    size_type n = last - first;
    if (n > 0) {
      vallocate(n);
      construct_at_end(end_ + n, first);
    }
  }

  vector(const vector& copy) : alloc_(copy.alloc_) {
    size_type n = copy.size();
    if (n > 0) {
      vallocate(n);
      construct_at_end(end_ + n, copy.begin());
    }
  }

  ~vector() { vdeallocate(); }
  vector& operator=(const vector& obj) {
    if (this != &obj) {
      this->assign(obj.begin(), obj.end());
    }
  }
  allocator_type get_allocator() const { return this->alloc_(); }

  /*
   * 반복자
   */
  iterator begin() { return begin_; }
  const_iterator begin() const { return begin_; }
  iterator end() { return end_; }
  const_iterator end() const { return end_; }
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

  size_type size() const { return end_ - begin_; }
  size_type max_size() const { return allocator_type().max_size(); }
  void resize(size_type n, const value_type& val = value_type()) {
    size_type s = size();
    if (s < n) {
      append(n - s, val);
    } else if (s > n) {
      destruct_at_end(begin_ + n);
    }
  }

  size_type capacity() const { return end_cap_ - begin_; }
  bool empty() const { return size() == 0 ? true : false; }
  void reserve(size_type n) {
    pointer p_begin = begin_;
    size_type p_size = size();
    size_type p_cap = capacity();
    vallocate(n);
    construct_at_end(begin_ + p_size, p_begin);
    alloc_.deallocate(p_begin, p_cap);
  }

  /*
   * Element access
   */
  reference at(size_type n) {
    if (n >= size()) throw std::out_of_range("vector");
    return begin_[n];
  }
  const_reference at(size_type n) const {
    if (n >= size()) throw std::out_of_range("vector");
    return begin_[n];
  }
  reference operator[](size_type n) { return begin_[n]; };
  const_reference operator[](size_type n) const { return begin_[n]; }
  reference front() { return *begin_; }
  const_reference front() const { return *begin_; }
  reference back() { return *(end_ - 1); }
  const_reference back() const { return *(end_ - 1); }

  /*
   * Modifiers
   */
  void assign(size_type n, const value_type& val) {
    if (n <= capacity()) {
      size_type s = size();
      std::fill_n(begin_, std::min(n, s), val);
      if (n > s) {
        size_type add_size = n - s;
        construct_at_end(end_ + add_size, val);
      } else
        destruct_at_end(begin_ + n);
    } else {
      vdeallocate();
      vallocate(recommand_cap(n));
      construct_at_end(end_ + n, val);
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
    if (end_ == end_cap_) {
      size_type new_size = recommand_cap(size() + 1);
      this->reserve(new_size);
    }
    construct_at_end(end_ + 1, val);
  }

  void pop_back() { destruct_at_end(end_ - 1); }

  iterator insert(iterator position, const value_type& val) {
    size_type d = position - begin_;
    if (end_ == end_cap_) {
      this->reserve(recommand_cap(1));
    }
    pointer pos = begin_ + d;
    if (pos == end_)
      alloc_.construct(end_, val);
    else {
      for (pointer old_end = end_; old_end != pos; --old_end)
        alloc_.construct(old_end, *(old_end - 1));
      ++end_;
      alloc_.construct(pos, val);
    }
    return pos;
  }

  template <class InputIterator>
  iterator insert(InputIterator position, size_type n, const value_type& val) {
    size_type d = position - begin_;
    if (end_cap_ < end_ + n) {
      this->reserve(recommand_cap(capacity() + d));
    }
    pointer pos = begin_ + d;
    if (pos == end_)
      construct_at_end(end_ + n, val);
    else {
      pointer back = end_ + n - 1;
      for (pointer old_end = end_; old_end != pos; --old_end, --back) {
        alloc_.construct(back, *(old_end - 1));
      }
      for (size_t i = 0; i < n; ++i, ++pos, ++end_) alloc_.construct(pos, val);
    }
    return pos - n;
  }

  template <class InputIterator>
  iterator insert(iterator position, InputIterator first, InputIterator last,
                  typename ft::enable_if<!ft::is_integral<InputIterator>::value,
                                         InputIterator>::type* = nullptr) {
    size_type off = position - begin_;
    size_type n = last - first;
    if (end_cap_ < end_ + n) {
      this->reserve(recommand_cap(capacity() + off));
    }
    pointer pos = begin_ + off;
    if (pos == end_)
      construct_at_end(end_ + n, *first);
    else {
      pointer back = end_ + n - 1;
      for (pointer old_end = end_; old_end != pos; --old_end, --back) {
        alloc_.construct(back, *(old_end - 1));
      }
      for (size_t i = 0; i < n; ++i, ++pos, ++end_, ++first)
        alloc_.construct(pos, *first);
    }
    return pos - n;
  }

  iterator erase(iterator position) {
    alloc_.destroy(position);
    size_type n = end_ - begin_ - 1;
    std::memcpy(position, position + 1, n * sizeof(value_type));
    *(end_ - 1) = 0;
    --end_;
    return (position);
  }

  iterator erase(iterator first, iterator last) {
    for (iterator pos = first; pos != last; ++pos) {
      alloc_.destroy(pos);
    }
    size_type move_n = end_ - last;
    size_type erase_n = last - first;
    std::memcpy(first, last, move_n * sizeof(value_type));
    std::memset(end_ - erase_n, 0, erase_n);
    end_ -= erase_n;
  }
  void swap(vector& x) {
    if (*this == x) return;
    std::swap(this->begin_, x.begin_);
    std::swap(this->end_, x.end_);
    std::swap(this->end_cap_, x.end_cap_);
  }
  void clear() { destruct_at_end(begin_); }

  bool operator==(const vector& y) {
    return this->size() == y.size() &&
           std::equal(this->begin(), this->end(), y.begin());
  }
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
