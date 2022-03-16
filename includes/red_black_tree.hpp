#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP
#include <exception>
#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>
#define NC "\e[0m"
#define RED_C "\e[31m"
#define BLACK_C "\e[30m \e[1m"
#define BLUE "\e[36m"

enum Color { RED, BLACK, DOUBLE_BLACK };

template <class T>
struct Node {
  T data;
  int color;
  Node *left, *right, *parent;

  Node() {
    this->data = 0;
    this->color = BLACK;
    left = right = parent = nullptr;
  }
};

template <class T>
class RBTree {
 private:
  typedef Node<T> Node;
  Node *root;
  Node *nil;

 public:
  RBTree() : root(nullptr), nil(new Node()) {}

  ~RBTree() {
    if (root) delete (root);
    delete (nil);
  }

  Node *get_root() { return this->root; }

  void set_color(Node *node, int color) {
    if (node == nullptr) throw std::out_of_range("set_color");
    node->color = color;
  }

  int get_color(Node *node) {
    if (node == nullptr) throw std::out_of_range("get_color");
    return node->color;
  }

  Node *create_node(int data) {
    Node *node = new Node();
    node->data = data;
    node->color = RED;
    node->left = node->right = this->nil;
    return node;
  }
  void insert_value(int data) {
    Node *new_node = create_node(data);
    insert_node(this->root, new_node);
    rebuild_insert(new_node);
  }

  void insert_node(Node *&root, Node *new_node) {
    if (root == nullptr) {
      root = new_node;
    }
    if (new_node->data < root->data) {
      if (root->left == nil) {
        root->left = new_node;
        new_node->parent = root;
      } else
        insert_node(root->left, new_node);
    } else if (new_node->data > root->data) {
      if (root->right == nil) {
        root->right = new_node;
        new_node->parent = root;
      } else
        insert_node(root->right, new_node);
    }
  }

  void rotate_left(Node *Parent) {
    Node *right_child = Parent->right;
    Parent->right = right_child->left;

    if (Parent->right != this->nil) Parent->right->parent = Parent;

    right_child->parent = Parent->parent;

    if (Parent->parent == nullptr)
      this->root = right_child;
    else if (Parent == Parent->parent->left)
      Parent->parent->left = right_child;
    else
      Parent->parent->right = right_child;
    right_child->left = Parent;
    Parent->parent = right_child;
  }

  void rotate_right(Node *Parent) {
    Node *left_child = Parent->left;
    Parent->left = left_child->right;

    if (Parent->left != this->nil) Parent->left->parent = Parent;

    left_child->parent = Parent->parent;

    if (Parent->parent == nullptr)
      this->root = left_child;
    else if (Parent == Parent->parent->left)
      Parent->parent->left = left_child;
    else
      Parent->parent->right = left_child;
    left_child->right = Parent;
    Parent->parent = left_child;
  }

  void rebuild_insert(Node *new_node) {
    Node *parent;
    Node *grand_parent;
    Node *uncle;
    while (new_node != this->root && get_color(new_node->parent) == RED) {
      parent = new_node->parent;
      grand_parent = parent->parent;
      if (parent == grand_parent->left) {
        uncle = grand_parent->right;
        if (get_color(uncle) == RED) {
          set_color(parent, BLACK);
          set_color(uncle, BLACK);
          set_color(grand_parent, RED);
        } else {
          if (new_node == parent->right) {
            rotate_left(parent);
            parent = new_node;
          }
          rotate_right(grand_parent);
          std::swap(parent->color, grand_parent->color);
        }
      } else {
        uncle = grand_parent->left;
        if (get_color(uncle) == RED) {
          set_color(parent, BLACK);
          set_color(uncle, BLACK);
          set_color(grand_parent, RED);
        } else {
          if (new_node == parent->left) {
            rotate_right(parent);
            parent = new_node;
          }
          rotate_left(grand_parent);
          std::swap(parent->color, grand_parent->color);
        }
      }
    }
    set_color(root, BLACK);
  }

  Node *search_node(Node *root, int data) {
    if (root == nullptr || root == nullptr) return nullptr;
    if (data < root->data)
      return search_node(root->left, data);
    else if (data > root->data)
      return search_node(root->right, data);
    else
      return root;
  }

  Node *min_node(Node *node) {
    if (node == this->nil || node == nullptr) return nullptr;
    if (node->left == this->nil)
      return node;
    else
      return min_node(node->left);
  }

  void rebuild_delete(Node *root, Node *successor) {
    Node *sibling;
    while (successor->parent && get_color(successor) == BLACK) {
      if (successor == successor->parent->left) {
        sibling = successor->parent->right;
        if (get_color(sibling) == RED) {
          set_color(sibling, BLACK);
          set_color(successor->parent, RED);
          rotate_left(successor->parent);
        } else {
          if (get_color(sibling->left) == BLACK &&
              get_color(sibling->right) == BLACK) {
            set_color(sibling, RED);
            successor = successor->parent;
          } else {
            if (get_color(sibling->left) == RED) {
              set_color(sibling->left, BLACK);
              set_color(sibling, RED);
              rotate_right(sibling);
              sibling = sibling->parent->right;
            }
            set_color(sibling, successor->parent->color);
            set_color(successor->parent, BLACK);
            set_color(sibling->right, BLACK);
            rotate_left(successor->parent);
            successor = root;
          }
        }
      } else {
        sibling = successor->parent->left;
        if (get_color(sibling) == RED) {
          set_color(sibling, BLACK);
          set_color(successor->parent, RED);
          rotate_right(successor->parent);
        } else {
          if (get_color(sibling->left) == BLACK &&
              get_color(sibling->right) == BLACK) {
            set_color(sibling, RED);
            successor = successor->parent;
          } else {
            if (get_color(sibling->right) == RED) {
              set_color(sibling->right, BLACK);
              set_color(sibling, RED);
              rotate_left(sibling);
              sibling = sibling->parent->left;
            }
            set_color(sibling, successor->parent->color);
            set_color(successor->parent, BLACK);
            set_color(sibling->left, BLACK);
            rotate_left(successor->parent);
            successor = root;
          }
        }
      }
    }
    set_color(successor, BLACK);
  }

  void delete_value(int data) {
    Node *target = search_node(root, data);
    Node *remove;
    Node *successor;

    if (target == nullptr) return;
    if (target->left == this->nil || target->right == this->nil)
      remove = target;
    else {
      remove = min_node(target->right);
      target->data = remove->data;
    }
    successor = (remove->left != this->nil) ? remove->left : remove->right;
    successor->parent = remove->parent;
    if (remove->parent == nullptr)
      root = successor;
    else {
      if (remove == remove->parent->left)
        remove->parent->left = successor;
      else
        remove->parent->right = successor;
    }
    if (get_color(remove) == BLACK) rebuild_delete(root, successor);
    delete (remove);
  }

  void node_info(Node *node) {
    if (node == this->nil) return;
    std::cout << "node:" << std::setw(3) << node->data << BLUE "|" NC;
    if (get_color(node) == RED)
      std::cout << std::setw(15) << RED_C "RED" NC << BLUE "|" NC;
    else if (get_color(node) == BLACK)
      std::cout << std::setw(15) << BLACK_C "BLACK" NC << BLUE "|" NC;
    if (node->left != this->nil) {
      std::cout << "left_node:" << std::setw(4) << node->left->data
                << BLUE "|" NC;
    } else {
      std::cout << "left_node:" << std::setw(4) << BLACK_C "nil" NC
                << BLUE "|" NC;
    }
    if (node->right != this->nil) {
      std::cout << "right_node:" << std::setw(4) << node->right->data
                << BLUE "|" NC;
    } else {
      std::cout << "right_node:" << std::setw(4) << BLACK_C "nil" NC
                << BLUE "|" NC;
    }
    std::cout << std::endl;
  }

  void print_tree() {
    std::queue<Node *> q;
    if (root) q.push(root);
    while (!q.empty()) {
      Node *node = q.front();
      q.pop();
      node_info(node);
      if (node->left) q.push(node->left);
      if (node->right) q.push(node->right);
    }
  }

  void delete_node(Node *tree) {
    if (tree == nullptr) return;
    if (tree->left != this->nil) delete_node(tree->left);
    if (tree->right != this->nil) delete_node(tree->right);
    delete (tree);
  }

  void delete_tree() {
    delete_node(this->root);
    this->root = nullptr;
  };
};
#endif