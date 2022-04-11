/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 20:51:20 by ulee              #+#    #+#             */
/*   Updated: 2022/04/10 22:33:43 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_ITERATOR_HPP
#define RBTREE_ITERATOR_HPP

#include "etc.hpp"

namespace ft {

template <class T, class TTT> class rb_tree_const_iterator;

template <class T, class NodePtr> class rb_tree_iterator {
  // * typedef
public:
  typedef T value_type;
  typedef T *pointer;
  typedef T &reference;
  typedef NodePtr node_pointer;
  typedef long difference_type;
  typedef unsigned long size_type;
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef ft::rb_tree_const_iterator<T, NodePtr> const_iterator;

private:
  // * private member
  node_pointer _node;

public:
  // * constructor
  rb_tree_iterator() {}

  rb_tree_iterator(const node_pointer x) : _node(x) {}

  rb_tree_iterator(const rb_tree_iterator &x) : _node(x.base()) {}

  rb_tree_iterator(const const_iterator &x) : _node(x.base()) {}

  ~rb_tree_iterator() {}

  node_pointer base() const { return _node; }

  // * operations
  void tree_min(node_pointer node) {
    while (node->left != u_nullptr)
      node = node->left;
    _node = node;
  }

  void tree_max(node_pointer node) {
    while (node->right != u_nullptr)
      node = node->right;
    _node = node;
  }

  rb_tree_iterator &operator=(const rb_tree_iterator &x) {
    _node = x._node;
    return (*this);
  }

  rb_tree_iterator &operator++() {
    if (_node->right != u_nullptr) {
      tree_min(_node->right);
      return *this;
    }
    while (!tree_is_left_child())
      _node = _node->parent;
    _node = _node->parent;
    return *this;
  }

  rb_tree_iterator operator++(int) {
    rb_tree_iterator temp(*this);
    ++(*this);
    return temp;
  }

  rb_tree_iterator &operator--() {
    if (_node->left != u_nullptr) {
      tree_max(_node->left);
      return *this;
    }
    while (tree_is_left_child())
      _node = _node->parent;
    _node = _node->parent;
    return *this;
  }

  rb_tree_iterator operator--(int) {
    rb_tree_iterator temp(*this);
    --(*this);
    return temp;
  }

  bool operator==(const rb_tree_iterator &x) const {
    return this->_node == x._node;
  }

  bool operator!=(const rb_tree_iterator &x) const {
    return this->_node != x._node;
  }

  reference operator*() const { return _node->data; }

  pointer operator->() const { return &_node->data; }

  bool tree_is_left_child() const { return _node == _node->parent->left; }
};

template <class T, class NodePtr> class rb_tree_const_iterator {
  // * typedef
public:
  typedef T value_type;
  typedef const T *pointer;
  typedef const T &reference;
  typedef NodePtr node_pointer;
  typedef long difference_type;
  typedef unsigned long size_type;
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef ft::rb_tree_iterator<T, NodePtr> non_const_iterator;

private:
  // * private member
  node_pointer _node;

public:
  // * constructor
  rb_tree_const_iterator() {}

  rb_tree_const_iterator(const node_pointer x) : _node(x) {}

  rb_tree_const_iterator(const rb_tree_const_iterator &x) : _node(x.base()) {}

  rb_tree_const_iterator(non_const_iterator x) : _node(x.base()) {}

  ~rb_tree_const_iterator() {}

  node_pointer base() const { return _node; }

  // * operations
  void tree_min(node_pointer node) {
    while (node->left != u_nullptr)
      node = node->left;
    _node = node;
  }

  void tree_max(node_pointer node) {
    while (node->right != u_nullptr)
      node = node->right;
    _node = node;
  }

  rb_tree_const_iterator &operator=(const rb_tree_const_iterator &x) {
    _node = x._node;
    return (*this);
  }

  rb_tree_const_iterator &operator++() {
    if (_node->right != u_nullptr) {
      tree_min(_node->right);
      return *this;
    }
    while (!tree_is_left_child())
      _node = _node->parent;
    _node = _node->parent;
    return *this;
  }

  rb_tree_const_iterator operator++(int) {
    rb_tree_const_iterator temp(*this);
    ++(*this);
    return temp;
  }

  rb_tree_const_iterator &operator--() {
    if (_node->left != u_nullptr) {
      tree_max(_node->left);
      return *this;
    }
    while (tree_is_left_child())
      _node = _node->parent;
    _node = _node->parent;
    return *this;
  }

  rb_tree_const_iterator operator--(int) {
    rb_tree_const_iterator temp(*this);
    --(*this);
    return temp;
  }

  bool operator==(const rb_tree_const_iterator &x) const {
    return this->_node == x._node;
  }

  bool operator!=(const rb_tree_const_iterator &x) const {
    return this->_node != x._node;
  }

  reference operator*() const { return _node->data; }

  pointer operator->() const { return &_node->data; }

  bool tree_is_left_child() const { return _node == _node->parent->left; }
};

} // namespace ft

#endif
