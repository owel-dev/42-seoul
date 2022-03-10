#include <iostream>

#include "red_black_tree.hpp"
#define typedef int element_type;

typedef struct node {
  struct node* parent;
  struct node* left;
  struct node* right;

  bool color;
  element_type data;
} node;

int main() {}