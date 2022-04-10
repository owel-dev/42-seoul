/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 20:51:36 by ulee              #+#    #+#             */
/*   Updated: 2022/04/08 20:51:36 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
#define SET_HPP

#include "RBTree.hpp"
#include "etc.hpp"
#include "reverse_iterator.hpp"
#include "set_iterator.hpp"

namespace ft
{

template<class T, class Compare = std::less <T>,
        class Alloc = std::allocator <T> >
class set
{
  public:
  // * typedef
  typedef T key_type;
  typedef T value_type;
  typedef Compare key_compare;
  typedef Compare value_compare;

  typedef Alloc allocator_type;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef typename allocator_type::difference_type difference_type;
  typedef typename allocator_type::size_type size_type;

  typedef ft::rb_tree<value_type, key_compare> tree_type;
  typedef ft::set_iterator<typename tree_type::iterator> iterator;
  typedef ft::set_const_iterator<typename tree_type::const_iterator>
          const_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

  private:
  // * private member
  key_compare _comp;
  allocator_type _alloc;
  tree_type _tree;

  public:
  // * constructor
  set(const key_compare &comp = key_compare(),
      const allocator_type &alloc = allocator_type())
          : _comp(comp), _alloc(alloc), _tree(value_compare(comp)) {}

  template<class InputIterator>
  set(InputIterator first, InputIterator last,
      const key_compare &comp = key_compare(),
      const allocator_type &alloc = allocator_type())
          : _comp(comp), _alloc(alloc), _tree(value_compare(_comp))
  {
    insert(first, last);
  }

  set(const set &x) : _comp(x._comp), _alloc(x._alloc), _tree(x._tree) {}

  ~set() {}

  set &operator=(const set &x)
  {
    if (this != &x) {
      this->clear();
      _alloc = x._alloc;
      _comp = x._comp;
      insert(x.begin(), x.end());
    }
    return (*this);
  }

  // * iterator
  iterator begin() { return _tree.begin(); }

  const_iterator begin() const { return _tree.begin(); }

  iterator end() { return _tree.end(); }

  const_iterator end() const { return _tree.end(); }

  reverse_iterator rbegin() { return reverse_iterator(_tree.end()); }

  const_reverse_iterator rbegin() const
  {
    return reverse_iterator(_tree.end());
  }

  reverse_iterator rend() { return reverse_iterator(_tree.begin()); }

  const_reverse_iterator rend() const
  {
    return reverse_iterator(_tree.begin());
  }

  // * capacity
  bool empty() const { return _tree.size() == 0; }

  size_type size() const { return _tree.size(); }

  size_type max_size() const { return _tree.max_size(); }

  // * modifiers
  ft::pair<iterator, bool> insert(const value_type &val)
  {
    return _tree.insert(val);
  }

  iterator insert(iterator position, const value_type &val)
  {
    return _tree.insert(position.base(), val);
  }

  template<class InputIterator>
  void insert(InputIterator first, InputIterator last)
  {
    _tree.insert(first, last);
  }

  void erase(iterator position) { _tree.erase(position.base()); }

  size_type erase(const value_type &val)
  {
    iterator target = find(val);
    if (target != end()) {
      erase(target);
      return 1;
    }
    return 0;
  }

  void erase(iterator first, iterator last)
  {
    while (first != last)
      erase(first++);
  }

  void swap(set &x)
  {
    _tree.swap(x._tree);
    std::swap(_comp, x._comp);
    std::swap(_alloc, x._alloc);
  }

  void clear() { _tree.clear(); }

  // * observers
  key_compare key_comp() const { return _comp; }

  value_compare value_comp() const { return _comp; }

  // * operations
  iterator find(const value_type &val) { return _tree.find(val); }

  const_iterator find(const value_type &val) const { return _tree.find(val); }

  size_type count(const key_type &k) const { return find(k) != end(); }

  iterator lower_bound(const key_type &k) { return _tree.lower_bound(k); }

  const_iterator lower_bound(const key_type &k) const
  {
    return _tree.lower_bound(k);
  }

  iterator upper_bound(const key_type &k) { return _tree.upper_bound(k); }

  const_iterator upper_bound(const key_type &k) const
  {
    return _tree.upper_bound(k);
  }

  pair<iterator, iterator> equal_range(const key_type &k)
  {
    return pair<iterator, iterator>(lower_bound(k), upper_bound(k));
  }

  pair<const_iterator, const_iterator> equal_range(const key_type &k) const
  {
    return pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
  }

  // * allocator
  allocator_type get_allocator() const { return _alloc; }
};

template<class T, class Comp, class Allocator>
bool operator==(const set<T, Comp, Allocator> &x,
                const set<T, Comp, Allocator> &y)
{
  return x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin());
}

template<class T, class Comp, class Allocator>
bool operator!=(const set<T, Comp, Allocator> &x,
                const set<T, Comp, Allocator> &y)
{
  return !(x == y);
}

template<class T, class Comp, class Allocator>
bool operator<(const set<T, Comp, Allocator> &x,
               const set<T, Comp, Allocator> &y)
{
  return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
}

template<class T, class Comp, class Allocator>
bool operator>(const set<T, Comp, Allocator> &x,
               const set<T, Comp, Allocator> &y)
{
  return y < x;
}

template<class T, class Comp, class Allocator>
bool operator<=(const set<T, Comp, Allocator> &x,
                const set<T, Comp, Allocator> &y)
{
  return !(y < x);
}

template<class T, class Comp, class Allocator>
bool operator>=(const set<T, Comp, Allocator> &x,
                const set<T, Comp, Allocator> &y)
{
  return !(x < y);
}

} // namespace ft

#endif // SET_HPP
