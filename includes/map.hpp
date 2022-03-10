#ifndef MAP_HPP
#define MAP_HPP

#include <exception>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>

template <class Key,                       // map::key_type
          class T,                         // map::mapped_type
          class Compare = std::less<Key>,  // map::key_compare
          class Alloc =
              std::allocator<ft::pair<const Key, T> >  // map::allocator_type
          >
class map {
 private:
 public:
  typedef Key key_type;
  typedef T mapped_type;
  typedef typename ft::pair<key_type, value_type> value_type;
  typedef Alloc allocator_type;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  // typedef ft::map_iterator<value_type> iterator;
  // typedef const ft::map_iterator<value_type> const_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef long difference_type;
  typedef unsigned long size_type;

  /*
   * basic
   */
  explicit map(const key_compare& comp = key_compare(),
               const allocator_type& alloc = allocator_type()) {}

  // template <class InputIterator>
  // map(InputIterator first, InputIterator last,
  //     const key_compare& comp = key_compare(),
  //     const allocator_type& alloc = allocator_type()) {}

  // map(const map& x) {}

  // ~map() {}

  // map& operator=(const map& x) {}

  /*
   * iterator
   */
  // iterator begin() {}

  // const_iterator begin() const {}

  // iterator end() {}

  // const_iterator end() const {}

  // reverse_iterator rbegin() {}

  // const_reverse_iterator rbegin() const {}

  // reverse_iterator rend() {}

  // const_reverse_iterator rend() const {}

  /*
   * capacity
   */
  // bool empty() const {}

  // size_type size() const {}

  // size_type max_size() const {}

  /*
   * access
   */

  // mapped_type& operator[](const key_type& k) {}

  /*
   * modifiers
   */

  // pair<iterator, bool> insert(const value_type& val) {}

  // iterator insert(iterator position, const value_type& val) {}

  // template <class InputIterator>
  // void insert(InputIterator first, InputIterator last) {}

  // void erase(iterator position) {}

  // size_type erase(const key_type& k) {}

  // void erase(iterator first, iterator last) {}

  // void swap(map& x) {}

  // void clear() {}

  /*
   * observers
   */
  // key_compare key_comp() const;

  // value_compare value_comp() const;

  /*
   * operations
   */
  // iterator find(const key_type& k);

  // const_iterator find(const key_type& k) const;

  // size_type count(const key_type& k) const;

  // iterator lower_bound(const key_type& k);

  // const_iterator lower_bound(const key_type& k) const;

  // iterator upper_bound(const key_type& k);

  // const_iterator upper_bound(const key_type& k) const;

  // pair<const_iterator, const_iterator> equal_range(const key_type& k) const;

  // pair<iterator, iterator> equal_range(const key_type& k);

  /*
   * allocator
   */
  // allocator_type get_allocator() const;
};

#endif