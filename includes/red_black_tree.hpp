#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP
#include <iostream>
#define typedef int element_type;

typedef struct node {
  struct node* parent;
  struct node* left;
  struct node* right;

  bool color;
  element_type data;
} node;

// class red_black_tree {
//  private:
//  public:
//   red_black_tree();
//   red_black_tree(const red_black_tree& obj);
//   ~red_black_tree();
//   red_black_tree& operator=(const red_black_tree& obj);
// };

#endif