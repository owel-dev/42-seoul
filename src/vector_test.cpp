#include "vector.hpp"

#include <iostream>
#include <iterator>
#include <memory>
#include <utility>
#include <vector>

#include "vector_test_utils.cpp"

void construct_void() {
  std::vector<int> v;
  ft::vector<int> my_v;
  std::cout << "[ construct_void ]" << std::endl;
  std::cout << "--------------------------" << std::endl;
  std::cout << "std_vector: "
            << "size: " << v.size() << " capacoty: " << v.capacity()
            << std::endl;
  print_vector<std::vector<int> >(v);

  std::cout << "my__vector: "
            << "size: " << my_v.size() << " capacoty: " << my_v.capacity()
            << std::endl;
  print_vector<ft::vector<int> >(my_v);
  std::cout << std::endl;
}

void construct_n_value() {
  std::vector<int> v(10, 7);
  ft::vector<int> my_v(10, 7);
  std::cout << "[ construct_n_value ]" << std::endl;
  std::cout << "--------------------------" << std::endl;
  std::cout << "std_vector: "
            << "size: " << v.size() << " capacoty: " << v.capacity()
            << std::endl;
  print_vector<std::vector<int> >(v);
  std::cout << "my__vector: "
            << "size: " << my_v.size() << " capacoty: " << my_v.capacity()
            << std::endl;
  print_vector<ft::vector<int> >(my_v);
  std::cout << std::endl;
}

void construct_iterator() {
  std::vector<int> v(7, 3);
  ft::vector<int> my_v(7, 3);

  std::cout << "[ construct_iterator ]" << std::endl;
  std::cout << "--------------------------" << std::endl;
  std::cout << "std_vector: "
            << "size: " << v.size() << " capacoty: " << v.capacity()
            << std::endl;
  print_vector<std::vector<int> >(v);
  std::cout << "my__vector: "
            << "size: " << my_v.size() << " capacoty: " << my_v.capacity()
            << std::endl;
  print_vector<ft::vector<int> >(my_v);
  std::cout << std::endl;
}

void modifier_push_back() {
  std::vector<int> v(3, 1);
  ft::vector<int> my_v(3, 1);

  std::cout << "[ modifier_push_back ]" << std::endl;
  std::cout << "--------------------------" << std::endl;
  std::cout << "std_vector: ";
  v.push_back(2);
  v.push_back(3);
  print_vector<std::vector<int> >(v);

  std::cout << "my_vector : ";
  my_v.push_back(2);
  my_v.push_back(3);
  print_vector<ft::vector<int> >(my_v);
  std::cout << std::endl;
}

void modifier_pop_back() {
  std::vector<int> v(1, 1);
  ft::vector<int> my_v(1, 1);

  std::cout << "[ modifier_pop_back ]" << std::endl;
  std::cout << "--------------------------" << std::endl;
  std::cout << "std_vector: ";
  v.push_back(2);
  v.push_back(3);
  v.pop_back();
  v.pop_back();
  std::cout << "std_vector: "
            << "size: " << v.size() << " capacoty: " << v.capacity()
            << std::endl;

  std::cout << "my__vector: ";
  my_v.push_back(2);
  my_v.push_back(3);
  my_v.pop_back();
  my_v.pop_back();
  std::cout << "my__vector: "
            << "size: " << my_v.size() << " capacoty: " << my_v.capacity()
            << std::endl;
  std::cout << std::endl;
}

void capacity_reserve() {
  std::vector<int> v(3, 10);
  ft::vector<int> my_v(3, 10);
  std::cout << "[ capacity_reserve ]" << std::endl;
  std::cout << "--------------------------" << std::endl;
  v.reserve(50);
  my_v.reserve(50);
  std::cout << "std_vector: "
            << "size: " << v.size() << " capacoty: " << v.capacity()
            << std::endl;
  std::cout << "my__vector: "
            << "size: " << my_v.size() << " capacoty: " << my_v.capacity()
            << std::endl;
  std::cout << std::endl;
}

void capacity_resize() {
  std::vector<int> v;
  ft::vector<int> my_v;
  std::cout << "[ capacity_resize ]" << std::endl;
  std::cout << "--------------------------" << std::endl;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  my_v.push_back(1);
  my_v.push_back(2);
  my_v.push_back(3);
  v.resize(10);
  my_v.resize(10);

  print_vector<std::vector<int> >(v);
  print_vector<ft::vector<int> >(my_v);
  std::cout << std::endl;
}

void access() {
  std::vector<int> v;
  ft::vector<int> my_v;
  std::cout << "[ access ]" << std::endl;
  std::cout << "--------------------------" << std::endl;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  v.push_back(4);
  v.push_back(5);

  my_v.push_back(1);
  my_v.push_back(2);
  my_v.push_back(3);
  my_v.push_back(4);
  my_v.push_back(5);

  std::cout << "std_vector: "
            << "at(3): " << v.size() << " vector[3]: " << v[3]
            << " front: " << v.front() << " back: " << v.back() << std::endl;
  std::cout << "my__vector: "
            << "at(3): " << my_v.size() << " vector[3]: " << my_v[3]
            << " front: " << my_v.front() << " back: " << my_v.back()
            << std::endl;
  std::cout << std::endl;
}

void modifier_assign() {
  std::vector<int> v(3, 1);
  ft::vector<int> my_v(3, 1);

  std::cout << "[ modifier_assign ]" << std::endl;
  std::cout << "--------------------------" << std::endl;

  v.assign(7, 3);
  std::cout << "std_vector: "
            << "size: " << v.size() << " capacity: " << v.capacity()
            << std::endl;
  print_vector<std::vector<int> >(v);

  my_v.assign(7, 3);
  std::cout << "my__vector: "
            << "size: " << my_v.size() << " capacity: " << my_v.capacity()
            << std::endl;
  print_vector<ft::vector<int> >(my_v);

  std::cout << std::endl;
}

void modifier_insert() {
  std::vector<int> v(3, 1);
  ft::vector<int> my_v(3, 1);

  std::cout << "[ modifier_insert ]" << std::endl;
  std::cout << "--------------------------" << std::endl;

  v.insert(v.begin() + 1, 7);
  std::cout << "std_vector: "
            << "size: " << v.size() << " capacity: " << v.capacity()
            << std::endl;
  print_vector<std::vector<int> >(v);

  my_v.insert(my_v.begin() + 1, 7);
  std::cout << "my__vector: "
            << "size: " << my_v.size() << " capacity: " << my_v.capacity()
            << std::endl;
  print_vector<ft::vector<int> >(my_v);

  v.insert(v.begin() + 2, 3, 9);
  std::cout << "std_vector: "
            << "size: " << v.size() << " capacity: " << v.capacity()
            << std::endl;
  print_vector<std::vector<int> >(v);

  my_v.insert(my_v.begin() + 2, 3, 9);
  std::cout << "my__vector: "
            << "size: " << my_v.size() << " capacity: " << my_v.capacity()
            << std::endl;
  print_vector<ft::vector<int> >(my_v);

  std::vector<int> test_vec(3, 8);

  v.insert(v.begin() + 7, test_vec.begin(), test_vec.end());
  std::cout << "std_vector: "
            << "size: " << v.size() << " capacity: " << v.capacity()
            << std::endl;
  print_vector<std::vector<int> >(v);

  my_v.insert(my_v.begin() + 7, test_vec.begin(), test_vec.end());
  std::cout << "std_vector: "
            << "size: " << my_v.size() << " capacity: " << my_v.capacity()
            << std::endl;
  print_vector<ft::vector<int> >(my_v);

  std::cout << std::endl;
}

void modifier_erase() {
  std::vector<int> v;
  ft::vector<int> my_v;

  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  v.push_back(4);
  v.push_back(5);
  v.push_back(6);
  v.push_back(7);

  my_v.push_back(1);
  my_v.push_back(2);
  my_v.push_back(3);
  my_v.push_back(4);
  my_v.push_back(5);
  my_v.push_back(6);
  my_v.push_back(7);

  std::cout << "[ modifier_erase ]" << std::endl;
  std::cout << "--------------------------" << std::endl;

  v.erase(v.begin() + 2);
  std::cout << "std_vector: "
            << "size: " << v.size() << " capacity: " << v.capacity()
            << std::endl;
  print_vector<std::vector<int> >(v);

  my_v.erase(my_v.begin() + 2);
  std::cout << "my__vector: "
            << "size: " << my_v.size() << " capacity: " << my_v.capacity()
            << std::endl;
  print_vector<ft::vector<int> >(my_v);
  std::cout << std::endl;

  v.erase(v.begin() + 1, v.begin() + 3);
  std::cout << "std_vector: "
            << "size: " << v.size() << " capacity: " << v.capacity()
            << std::endl;
  print_vector<std::vector<int> >(v);

  my_v.erase(my_v.begin() + 1, my_v.begin() + 3);
  std::cout << "my__vector: "
            << "size: " << my_v.size() << " capacity: " << my_v.capacity()
            << std::endl;
  print_vector<ft::vector<int> >(my_v);

  std::cout << std::endl;
}

void modifier_swap() {
  std::vector<int> v;
  std::vector<int> v2;

  ft::vector<int> my_v;
  ft::vector<int> my_v2;
  std::cout << "[ modifier_swap ]" << std::endl;
  std::cout << "--------------------------" << std::endl;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  v.push_back(4);
  v.push_back(5);

  v2.push_back(11);
  v2.push_back(21);
  v2.push_back(31);
  v2.push_back(41);
  v2.push_back(51);

  my_v.push_back(1);
  my_v.push_back(2);
  my_v.push_back(3);
  my_v.push_back(4);
  // my_v.push_back(5);

  my_v2.push_back(11);
  my_v2.push_back(12);
  my_v2.push_back(13);
  my_v2.push_back(14);
  my_v2.push_back(15);

  std::cout << "std_vector: "
            << "size: " << v.size() << " capacity: " << v.capacity()
            << std::endl;
  print_vector<std::vector<int> >(v);

  std::cout << "std_vector2: "
            << "size: " << v2.size() << " capacity: " << v2.capacity()
            << std::endl;
  print_vector<std::vector<int> >(v2);
  std::cout << std::endl;

  v.swap(v2);

  std::cout << "std_vector: "
            << "size: " << v.size() << " capacity: " << v.capacity()
            << std::endl;
  print_vector<std::vector<int> >(v);

  std::cout << "std_vector2: "
            << "size: " << v2.size() << " capacity: " << v2.capacity()
            << std::endl;
  print_vector<std::vector<int> >(v2);
  std::cout << std::endl;

  std::cout << "my__vector: "
            << "size: " << my_v.size() << " capacity: " << my_v.capacity()
            << std::endl;
  print_vector<ft::vector<int> >(my_v);
  std::cout << std::endl;

  std::cout << "my__vector2: "
            << "size: " << my_v2.size() << " capacity: " << my_v2.capacity()
            << std::endl;
  print_vector<ft::vector<int> >(my_v2);
  std::cout << std::endl;

  my_v.swap(my_v2);

  std::cout << "my__vector: "
            << "size: " << my_v.size() << " capacity: " << my_v.capacity()
            << std::endl;
  print_vector<ft::vector<int> >(my_v);
  std::cout << std::endl;

  std::cout << "my__vector2: "
            << "size: " << my_v2.size() << " capacity: " << my_v2.capacity()
            << std::endl;
  print_vector<ft::vector<int> >(my_v2);
  std::cout << std::endl;
}
