#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <stack>
#include <utility>
#include <vector>

// #include "map.hpp"
#include "RBTree.hpp"
#include "RBTree_test.cpp"
#include "map_test.cpp"
// #include "stack_test.cpp"
// #include "vector.hpp"
// #include "vector_test.cpp"

int main()
{
    /*
     * vector 테스트
     */
    // vector_construct_void();
    // vector_construct_n_value();
    // vector_construct_iterator();

    // vector_modifier_push_back();
    // vector_modifier_pop_back();
    // vector_modifier_assign();
    // vector_modifier_insert();
    // vector_modifier_erase();
    // vector_modifier_swap();

    // vector_capacity_reserve();
    // vector_capacity_resize();
    // vector_access();

    // vector_construct_copy();
    // vector_relation_operators();
    // vector_reverse_iterator();

    // stack_member_functions();
    // stack_relation_operators();

    RBTree_test();
    // map_modifier_insert();

    // std::map<int, int> m1;
    // m1.insert(std::pair<int, int>(2, 999));
    // m1.insert(std::pair<int, int>(1, 999));
    // // m1.insert(std::pair<int, int>(3, 999));
    // std::map<int, int>::iterator it2 = m1.end();
    // for (std::map<int, int>::iterator it = m1.begin(); it != m1.end(); ++it)
    // {
    //   std::cout << it->first << std::endl;
    // }

    // std::vector<int> v = std::vector<int>(5, 7);
    // for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
    //   std::cout << *it << std::endl;

    /*
     * map 테스트
     */
}