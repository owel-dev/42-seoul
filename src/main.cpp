#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <utility>
#include <vector>

#include "vector.hpp"
#include "vector_test.cpp"

int main() {
  construct_void();
  construct_n_value();
  construct_iterator();

  modifier_push_back();
  modifier_pop_back();
  modifier_assign();
  modifier_insert();
  modifier_erase();
  modifier_swap();

  capacity_reserve();
  capacity_resize();
  access();

  construct_copy();
  relation_operators();
  reverse_iterator();
  // std::vector<int> v = std::vector<int>(5, 7);
  // for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
  //   std::cout << *it << std::endl;
}