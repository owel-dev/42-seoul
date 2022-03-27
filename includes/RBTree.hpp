#ifndef RBTREE_HPP
#define RBTREE_HPP
#include <__tree>
#include <exception>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <utility>
#include <vector>

#include "RBTree_iterator.hpp"
#include "etc.hpp"

namespace ft {

template <class Key, class T, class Compare, class Node = ft::rb_node<T>,
          class Alloc = std::allocator<Node> >
class rb_tree {
public:
  typedef T value_type;
  typedef T &reference;
  typedef const T &const_reference;
  typedef Node node_type;
  typedef Node *node_pointer;
  typedef Node *&node_reference;

  typedef unsigned long size_type;
  typedef Alloc allocator_type;
  // typedef Node_Alloc node_allocator;
  typedef Compare compare_type;
  typedef ft::rb_tree_iterator<value_type> iterator;
  typedef ft::rb_tree_iterator<const value_type> const_iterator;

private:
  node_pointer _begin;
  node_pointer _end;
  size_type _size;
  allocator_type _alloc;
  compare_type _comp;

public:
  rb_tree(const allocator_type &alloc = allocator_type(),
          const compare_type &comp = compare_type())
      : _alloc(alloc), _comp(comp), _size(0) {
    _end = _alloc.allocate(1);
    _alloc.construct(_end, Node());
    _begin = _end;
  }

  rb_tree(const rb_tree &x)
      : _begin(x._begin), _end(x._end), _alloc(x.alloc), _comp(x._comp),
        _size(x._size) {}

  ~rb_tree() { delete_tree(); }

  node_pointer root() { return _end->left; }

  node_pointer *rootPtr() { return &_end->left; }

  node_pointer begin() { return _begin; }

  node_pointer end() { return _end; }

  size_type size() { return _size; }

  bool is_left_child(node_pointer node) { return node == node->parent->left; }

  node_pointer min_node(node_pointer node) {
    node_pointer temp = node;
    while (temp->left != nullptr)
      temp = temp->left;
    return temp;
  }

  node_pointer max_node(node_pointer node) {
    node_pointer temp = node;
    while (temp->right != nullptr)
      temp = temp->right;
    return temp;
  }

  node_pointer create_node(const_reference data) {
    node_pointer temp = _alloc.allocate(1);
    _alloc.construct(temp, Node(data));
    return temp;
  }

  node_pointer next_node(node_pointer node) {
    if (node->right != nullptr)
      return min_node(node->right);
    while (!is_left_child(node))
      node = node->parent;
    return node->parent;
  }

  void rotate_left(node_pointer node) {
    node_pointer right_child = node->right;
    node->right = right_child->left;
    if (node->right != nullptr)
      node->right->parent = node;
    right_child->parent = node->parent;
    if (is_left_child(node))
      node->parent->left = right_child;
    else
      node->parent->right = right_child;
    right_child->left = node;
    node->parent = right_child;
  }

  void rotate_right(node_pointer node) {
    node_pointer left_child = node->left;
    node->left = left_child->right;
    if (node->left != nullptr)
      node->left->parent = node;
    left_child->parent = node->parent;
    if (is_left_child(node))
      node->parent->left = left_child;
    else
      node->parent->right = left_child;
    left_child->right = node;
    node->parent = left_child;
  }

  node_pointer &find_node(node_pointer &parent, const_reference data) {
    node_pointer node = root();
    node_pointer *p_node = rootPtr();

    if (node != nullptr) {
      while (true) {
        if (_comp(data, node->data)) {
          if (node->left != nullptr) {
            p_node = &(node->left);
            node = node->left;
          } else {
            parent = node;
            return parent->left;
          }
        } else if (_comp(node->data, data)) {
          if (node->right != nullptr) {
            p_node = &node->right;
            node = node->right;
          } else {
            parent = node;
            return parent->right;
          }
        } else {
          parent = node;
          return *p_node;
        }
      }
    }
    parent = _end;
    return _end->left;
  }

  node_pointer &find_node(iterator hint, node_pointer &parent,
                          node_pointer &dummy, const_reference data) {
    if (hint == end() || _comp(data, *hint)) {
      iterator prev = hint;
      if (hint == begin() || _comp(*--prev, data)) {
        if (hint._node->left == nullptr) {
          parent = hint._node;
          return parent->left;
        } else {
          parent = prev._node;
          return prev._node->right;
        }
      }
      return find_node(parent, data);
    } else if (_comp(*hint, data)) {
      iterator next = hint;
      ++next;
      if (next == end() || _comp(data, *next)) {
        if (hint._node->right == nullptr) {
          parent = hint._node;
          return hint._node->right;
        } else {
          parent = next._node;
          return parent->left;
        }
      }
      return find_node(parent, data);
    }
    parent = hint._node;
    dummy = hint._node;
    return dummy;
  }

  void rebuild_insert(node_pointer new_node) {
    new_node->is_black = new_node == root();
    while (new_node != root() && !new_node->parent->is_black) {
      if (is_left_child(new_node->parent)) {
        node_pointer uncle = new_node->parent->parent->right;
        if (uncle != nullptr && !uncle->is_black) {
          new_node = new_node->parent;
          new_node->is_black = true;
          new_node = new_node->parent;
          new_node->is_black = new_node == _begin;
          uncle->is_black = true;
        } else {
          if (!is_left_child(new_node)) {
            new_node = new_node->parent;
            rotate_left(new_node);
          }
          new_node = new_node->parent;
          new_node->is_black = true;
          new_node = new_node->parent;
          new_node->is_black = false;
          rotate_right(new_node);
          break;
        }
      } else {
        node_pointer uncle = new_node->parent->parent->left;
        if (uncle != nullptr && !uncle->is_black) {
          new_node = new_node->parent;
          new_node->is_black = true;
          new_node = new_node->parent;
          new_node->is_black = new_node == root();
          uncle->is_black = true;
        } else {
          if (is_left_child(new_node)) {
            new_node = new_node->parent;
            rotate_right(new_node);
          }
          new_node = new_node->parent;
          new_node->is_black = true;
          new_node = new_node->parent;
          new_node->is_black = false;
          rotate_left(new_node);
          break;
        }
      }
    }
  }

  pair<iterator, bool> insert_node(const_reference data) {
    node_pointer Parent;
    node_pointer new_node = create_node(data);
    node_pointer &dest = find_node(Parent, data);
    bool inserted = false;
    if (dest == nullptr) {
      dest = new_node;
      dest->parent = Parent;
      if (_begin->left != nullptr)
        _begin = _begin->left;
      rebuild_insert(new_node);
      inserted = true;
      ++_size;
    }
    return pair<iterator, bool>(iterator(dest), inserted);
  }

  iterator insert_node(iterator hint, const_reference data) {
    node_pointer Parent;
    node_pointer new_node = create_node(data);
    node_pointer dummy;
    node_pointer &dest = find_node(hint, Parent, dummy, data);
    if (dest == nullptr) {
      dest = new_node;
      dest->parent = Parent;
      if (_begin->left != nullptr)
        _begin = _begin->left;
      rebuild_insert(new_node);
      ++_size;
    }
    return iterator(dest);
  }

  void remove_node(node_pointer root, node_pointer node) {
    node_pointer remove = (node->left == nullptr || node->right == nullptr)
                              ? node
                              : next_node(node);
    node_pointer succesor =
        remove->left != nullptr ? remove->left : remove->right;
    node_pointer sibling = nullptr;
    if (succesor != nullptr)
      succesor->parent = remove->parent;
    if (is_left_child(remove)) {
      remove->parent->left = succesor;
      if (remove != root)
        sibling = remove->parent->right;
      else
        root = succesor;
    } else {
      remove->parent->right = succesor;
      sibling = remove->parent->left;
    }
    bool removed_black = remove->is_black;
    if (remove != node) {
      remove->parent = node->parent;
      if (is_left_child(node))
        remove->parent->left = remove;
      else
        remove->parent->right = remove;
      remove->left = node->left;
      remove->left->parent = remove;
      remove->right = node->right;
      if (remove->right != nullptr)
        remove->right->parent = remove;
      remove->is_black = node->is_black;
      if (root == node)
        root = remove;
    }
    if (removed_black && root != nullptr) {
      if (succesor != nullptr)
        succesor->is_black = true;
      else {
        while (true) {
          if (!is_left_child(sibling)) {
            if (!sibling->is_black) {
              sibling->is_black = true;
              sibling->parent->is_black = false;
              rotate_left(sibling->parent);
              if (root == sibling->left)
                root = sibling;
              sibling = sibling->left->right;
            }
            if ((sibling->left == nullptr || sibling->left->is_black) &&
                (sibling->right == nullptr || sibling->right->is_black)) {
              sibling->is_black = false;
              succesor = sibling->parent;
              if (succesor == root || !succesor->is_black) {
                succesor->is_black = true;
                break;
              }
              sibling = is_left_child(succesor) ? succesor->parent->right
                                                : succesor->parent->left;
            } else {
              if (sibling->right == nullptr || sibling->right->is_black) {
                sibling->left->is_black = true;
                sibling->is_black = false;
                rotate_right(sibling);
                sibling = sibling->parent;
              }
              sibling->is_black = sibling->parent->is_black;
              sibling->parent->is_black = true;
              sibling->right->is_black = true;
              rotate_left(sibling->parent);
              break;
            }
          } else {
            if (!sibling->is_black) {
              sibling->is_black = true;
              sibling->parent->is_black = false;
              rotate_right(sibling->parent);
              if (root == sibling->right)
                root = sibling;
              sibling = sibling->right->left;
            }
            if ((sibling->left == nullptr || sibling->left->is_black) &&
                (sibling->right == nullptr || sibling->right->is_black)) {
              sibling->is_black = false;
              succesor = sibling->parent;
              if (!succesor->is_black || succesor == root) {
                succesor->is_black = true;
                break;
              }
              sibling = is_left_child(succesor) ? succesor->parent->right
                                                : succesor->parent->left;
            } else {
              if (sibling->left == nullptr || sibling->left->is_black) {
                sibling->right->is_black = true;
                sibling->is_black = false;
                rotate_left(sibling);
                sibling = sibling->parent;
              }
              sibling->is_black = sibling->parent->is_black;
              sibling->parent->is_black = true;
              sibling->left->is_black = true;
              rotate_right(sibling->parent);
              break;
            }
          }
        }
      }
    }
  }
  void delete_node(const_reference value) {
    node_pointer remove = find_node(remove, value);
    if (remove != nullptr)
      remove_node(root(), remove);
    --_size;
  }

  void free_node(node_pointer node) {
    if (node == nullptr)
      return;
    if (node->left)
      free_node(node->left);
    if (node->right)
      free_node(node->right);
    _alloc.destroy(node);
    _alloc.deallocate(node, 1);
  }

  void delete_tree() {
    free_node(root());
    _alloc.destroy(_end);
    _alloc.deallocate(_end, 1);
  }

  void node_info(node_pointer node) const {
    if (node == nullptr)
      return;
    std::cout << "node:" << std::setw(3) << node->data << BLUE "|" NC;
    if (!node->is_black)
      std::cout << std::setw(15) << RED_C "RED" NC << BLUE "|" NC;
    else if (node->is_black)
      std::cout << std::setw(15) << BLACK_C "BLACK" NC << BLUE "|" NC;
    if (node->left) {
      std::cout << "left_node:" << std::setw(4) << node->left->data
                << BLUE "|" NC;
    } else {
      std::cout << "left_node:" << std::setw(4) << " " << BLUE "|" NC;
    }
    if (node->right) {
      std::cout << "right_node:" << std::setw(4) << node->right->data
                << BLUE "|" NC;
    } else {
      std::cout << "right_node:" << std::setw(4) << " " << BLUE "|" NC;
    }
    std::cout << std::endl;
  }

  void print_tree() const {
    std::queue<node_pointer> q;
    if (_end->left)
      q.push(_end->left);
    while (!q.empty()) {
      node_pointer node = q.front();
      q.pop();
      node_info(node);
      if (node->left)
        q.push(node->left);
      if (node->right)
        q.push(node->right);
    }
  }
};

}; // namespace ft

#endif