#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <stack>
#include <utility>
#include <vector>

// #include "map.hpp"
// #include "map_test.cpp"
#include "vector.hpp"
#include "vector_test.cpp"

int main() {
  /*
   * vector 테스트
   */
  vector_construct_void();
  vector_construct_n_value();
  vector_construct_iterator();

  vector_modifier_push_back();
  vector_modifier_pop_back();
  vector_modifier_assign();
  vector_modifier_insert();
  vector_modifier_erase();
  vector_modifier_swap();

  vector_capacity_reserve();
  vector_capacity_resize();
  vector_access();

  vector_construct_copy();
  vector_relation_operators();
  vector_reverse_iterator();

  // std::vector<int> v = std::vector<int>(5, 7);
  // for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
  //   std::cout << *it << std::endl;

  /*
   * map 테스트
   */
}