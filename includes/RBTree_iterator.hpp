#ifndef RBTREE_ITERATOR_HPP
#define RBTREE_ITERATOR_HPP

#include "etc.hpp"

namespace ft
{

template<class T, class NodePtr>
class rb_tree_iterator
{
  // * typedef
  public:
  typedef T value_type;
  typedef T *pointer;
  typedef T &reference;
  typedef NodePtr node_pointer;
  typedef long difference_type;
  typedef unsigned long size_type;

  private:
  // * private member
  node_pointer _node;

  public:
  // * constructor
  rb_tree_iterator() {}

  rb_tree_iterator(const node_pointer x) : _node(x) {}

  rb_tree_iterator(const rb_tree_iterator &x) : _node(x._node) {}

  ~rb_tree_iterator() {}

  node_pointer get_node() {
    return _node;
  }

  // * operations
  void tree_min(node_pointer node) {
    while (node->left != nullptr)
      node = node->left;
    _node = node;
  }

  void tree_max(node_pointer node) {
    while (node->right != nullptr)
      node = node->right;
    _node = node;
  }

  rb_tree_iterator &operator=(const rb_tree_iterator &x) {
    _node = x._node;
    return (*this);
  }

  rb_tree_iterator &operator++() {
    if (_node->right != nullptr) {
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
    if (_node->left != nullptr) {
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

  bool tree_is_left_child() const {
    return _node == _node->parent->left;
  }
};

}; // namespace ft

#endif