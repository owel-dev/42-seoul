#ifndef RBTREE_HPP
#define RBTREE_HPP

#include "RBTree_iterator.hpp"
#include "etc.hpp"
#include <queue>

namespace ft
{

template<class T, class Compare>
class rb_tree
{
  public:
  // * typedef
  typedef T value_type;
  typedef T &reference;
  typedef const T &const_reference;
  typedef Compare compare_type;
  typedef ft::rb_node<T> node_type;
  typedef node_type *node_pointer;

  typedef std::allocator<node_type> allocator_type;
  typedef typename allocator_type::size_type size_type;
  typedef typename allocator_type::difference_type difference_type;

  typedef ft::rb_tree_iterator<value_type, node_pointer> iterator;
  typedef ft::rb_tree_iterator<value_type, node_pointer> const_iterator;

  private:
  // * private member
  node_pointer _begin;
  node_pointer _end;
  size_type _size;
  allocator_type _alloc;
  compare_type _comp;

  public:
  // * constructor
  rb_tree(const compare_type &comp = compare_type())
          : _size(0), _alloc(allocator_type()), _comp(comp)
  {
    _end = _alloc.allocate(1);
    _alloc.construct(_end, node_type());
    _begin = _end;
  }

  rb_tree(const rb_tree &x)
          : _size(0)
  {
    _end = _alloc.allocate(1);
    _alloc.construct(_end, node_type());
    _begin = _end;
    *this = x;
  }

  rb_tree &operator=(const rb_tree &x)
  {
    if (this != x) {
      clear();
      _alloc = x._alloc;
      _comp = x._comp;
      insert(x.begin(), x.end());
    }
    return (*this);
  }

  ~rb_tree()
  {
    clear();
    _alloc.destroy(_end);
    _alloc.deallocate(_end, 1);
  }

  // * tree
  node_pointer root() { return _end->left; }

  node_pointer *rootPtr() { return &_end->left; }

  bool is_left_child(node_pointer node) { return node == node->parent->left; }

  node_pointer min_node(node_pointer node)
  {
    node_pointer temp = node;
    while (temp->left != nullptr)
      temp = temp->left;
    return temp;
  }

  node_pointer max_node(node_pointer node)
  {
    node_pointer temp = node;
    while (temp->right != nullptr)
      temp = temp->right;
    return temp;
  }

  node_pointer create_node(const_reference data)
  {
    node_pointer temp = _alloc.allocate(1);
    _alloc.construct(temp, node_type(data));
    return temp;
  }

  node_pointer next_node(node_pointer node)
  {
    if (node->right != nullptr)
      return min_node(node->right);
    while (!is_left_child(node))
      node = node->parent;
    return node->parent;
  }

  void rotate_left(node_pointer node)
  {
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

  void rebuild_insert(node_pointer new_node)
  {
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

  iterator remove_node_pointer(node_pointer node)
  {
    iterator it(node);
    ++it;
    if (node == _begin)
      _begin = it.get_node();
    remove_node(root(), node);
    --_size;
    return it;
  }

  void remove_node(node_pointer root, node_pointer node)
  {
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

  void delete_node(const_reference value)
  {
    node_pointer remove = find_pos(remove, value);
    if (remove != nullptr)
      remove_node(root(), remove);
    --_size;
  }

  void delete_tree(node_pointer node)
  {
    if (node != nullptr) {
      delete_tree(node->left);
      delete_tree(node->right);
      _alloc.destroy(node);
      _alloc.deallocate(node, 1);
    }
  }

  node_pointer &find_pos(node_pointer &parent, const_reference data)
  {
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

  node_pointer &find_pos(iterator hint, node_pointer &parent,
                         node_pointer &dummy, const_reference data)
  {
    if (hint == end() || _comp(data, *hint)) {
      iterator prev = hint;
      if (hint == begin() || _comp(*--prev, data)) {
        if (hint.get_node()->left == nullptr) {
          parent = hint.get_node();
          return parent->left;
        } else {
          parent = prev.get_node();
          return prev.get_node()->right;
        }
      }
      return find_pos(parent, data);
    } else if (_comp(*hint, data)) {
      iterator next = hint;
      ++next;
      if (next == end() || _comp(data, *next)) {
        if (hint.get_node()->right == nullptr) {
          parent = hint.get_node();
          return hint.get_node()->right;
        } else {
          parent = next.get_node();
          return parent->left;
        }
      }
      return find_pos(parent, data);
    }
    parent = hint.get_node();
    dummy = hint.get_node();
    return dummy;
  }

  void rotate_right(node_pointer node)
  {
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

  void node_info(node_pointer node) const
  {
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

  void print_tree() const
  {
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

  // * map

  // * iterator
  iterator begin() { return iterator(_begin); }

  const_iterator begin() const { return const_iterator(_begin); }

  iterator end() { return iterator(_end); }

  const_iterator end() const { return const_iterator(_end); }

  // * capacity
  size_type size() const { return _size; }

  size_type max_size() const
  {
    return std::min<size_type>(_alloc.max_size(),
                               std::numeric_limits<difference_type>::max());
  }

  // * opearations
  template<class Key>
  iterator find(const Key &k)
  {
    iterator it = lower_bound(k, root(), _end);
    if (it != end() && !_comp(k, *it))
      return it;
    return end();
  }

  template<class Key>
  const_iterator find(const Key &k) const
  {
    iterator it = lower_bound(k, root(), _end);
    if (it != end() && !_comp(k, *it))
      return it;
    return end();
  }

  template<class Key>
  iterator lower_bound(const Key &k,
                       node_pointer root_node, node_pointer result)
  {
    while (root_node != nullptr) {
      if (!_comp(root_node->data, k)) {
        result = root_node;
        root_node = root_node->left;
      } else
        root_node = root_node->right;
    }
    return iterator(result);
  }

  template<class Key>
  const_iterator lower_bound(const Key &k,
                             node_pointer root_node, node_pointer result) const
  {
    while (root_node != nullptr) {
      if (!_comp(root_node->data, k)) {
        result = root_node;
        root_node = root_node->left;
      } else
        root_node = root_node->right;
    }
    return const_iterator(result);
  }

  template<class Key>
  iterator upper_bound(const Key &k,
                       node_pointer root_node, node_pointer result)
  {
    while (root_node != nullptr) {
      if (_comp(k, root_node->data)) {
        result = root_node;
        root_node = root_node->left;
      } else
        root_node = root_node->right;
    }
    return iterator(result);
  }

  template<class Key>
  const_iterator upper_bound(const Key &k,
                             node_pointer root_node, node_pointer result) const
  {
    while (root_node != nullptr) {
      if (_comp(k, root_node->data)) {
        result = root_node;
        root_node = root_node->left;
      } else
        root_node = root_node->right;
    }
    return const_iterator(result);
  }

  // * modifiers
  void swap(rb_tree &x)
  {
    std::swap(_end, x._end);
    std::swap(_begin, x._begin);
    std::swap(_comp, x._comp);
    std::swap(_alloc, x._alloc);
    std::swap(_size, x._size);
  }

  pair<iterator, bool> insert(const_reference data)
  {
    node_pointer Parent;
    node_pointer new_node = create_node(data);
    node_pointer &dest = find_pos(Parent, data);
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
//    node_pointer ret = reinterpret_cast<node_pointer>(dest);
    return pair<iterator, bool>(iterator(dest), inserted);
  }

  iterator insert(iterator hint, const_reference data)
  {
    node_pointer Parent;
    node_pointer new_node = create_node(data);
    node_pointer dummy;
    node_pointer &dest = find_pos(hint, Parent, dummy, data);
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

  template<class InputIterator>
  void insert(InputIterator first, InputIterator last)
  {
    for (iterator it = end(); first != last; ++first)
      insert(it, *first);
  }

  void erase(iterator pos)
  {
    remove_node_pointer(pos.get_node());
  }

  void clear()
  {
    delete_tree(root());
    _begin = _end;
    _size = 0;
    _end->left = nullptr;
  }
};

}; // namespace ft

#endif