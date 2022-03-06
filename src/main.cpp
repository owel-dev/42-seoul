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
  capacity_reserve();
  capacity_resize();
  access();
  // int a[5] = {1, 2, 3, 4, 5};
  // std::vector<int *> v;
  // v.push_back(a);
  // v.push_back(a + 1);
  // v.push_back(a + 2);
  // for (std::vector<int *>::iterator it = v.begin(); it != v.end(); ++it) {
  //   std::cout << *it << std::endl;

  // std::cout << "#2: #size10 size: " << v2.size() << std::endl;
  // std::cout << "#2: #size10 size: " << _v2.size() << std::endl;

  // std::cout << "#3: #max_size size: " << v2.max_size() << std::endl;
  // std::cout << "#3: #max_size size: " << _v2.max_size() << std::endl;

  // std::cout << "#4: #capacity size: " << v2.capacity() << std::endl;
  // std::cout << "#4: #capacity size: " << _v2.capacity() << std::endl;

  // v2.push_back(10);
  // v2.push_back(7);
  // std::cout << "#5: #push_back size: " << v2.size()
  //           << " capacity: " << v2.capacity() << " front: " << v2.front()
  //           << " back: " << v2.back() << std::endl;

  // for (std::vector<int>::iterator it = v2.begin(); it != v2.end(); ++it)
  //   std::cout << *it << std::endl;

  // // _v2.push_back(10);
  // // _v2.push_back(7);
  // std::cout << "#5: #push_back size: " << _v2.size()
  //           << " capacity: " << _v2.capacity() << " front: " << _v2.front()
  //           << " back: " << _v2.back() << std::endl;

  // for (ft::vector<int>::iterator it = _v2.begin(); it != _v2.end(); ++it)
  //   std::cout << *it << std::endl;

  // try {
  //   std::cout << "#6: #at: " << v2.at(0) << std::endl;
  //   std::cout << "#6: #at: " << _v2.at(0) << std::endl;
  // } catch (const std::exception& e) {
  //   std::cerr << e.what() << '\n';
  // }

  // try {
  //   std::cout << "#7: #at_exception: " << _v2.at(3) << std::endl;
  // } catch (const std::exception& e) {
  //   std::cerr << e.what() << '\n';
  // }

  // try {
  //   std::cout << "#7: #at_exception: " << v2.at(3) << std::endl;
  // } catch (const std::exception& e) {
  //   std::cerr << e.what() << '\n';
  // }

  // // v2.push_back(12);
  // // _v2.push_back(12);
  // // v2.pop_back();
  // // _v2.pop_back();
  // std::cout << "#8: #pop_back size: " << v2.size()
  //           << " capacity: " << v2.capacity() << " front: " << v2.front()
  //           << " back: " << v2.back() << std::endl;

  // std::cout << "#8: #pop_back size: " << _v2.size()
  //           << " capacity: " << _v2.capacity() << " front: " << _v2.front()
  //           << " back: " << _v2.back() << std::endl;

  // int a[3] = {0, 1, 2};
  // std::cout << a[-100] << std::endl;
}