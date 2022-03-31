#include "map.hpp"
#include "vector.hpp"

#include <__tree>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <stack>
#include <utility>
#include <vector>

template<class T>
void print_map(T &v) {
  for (typename T::iterator it = v.begin(); it != v.end(); ++it)
    std::cout << it->first << " ";
  std::cout << std::endl;
}

void map_modifier_insert_1() {
  std::cout << "[ map_modifier_insert_1 ]" << std::endl;
  std::cout << "--------------------------" << std::endl;

  std::map<int, std::string> m;
  ft::map<int, std::string> my_m;

  m.insert(std::make_pair(4, "4"));
  m.insert(std::make_pair(3, "3"));
  m.insert(std::make_pair(1, "1"));
  m.insert(std::make_pair(2, "2"));

  std::pair<std::map<int, std::string>::iterator, bool> p =
          m.insert(std::make_pair(2, "2"));
  if (!p.second) {
    p.first->second = "hi";
  }

  std::cout << "std_map: "
            << "size: " << m.size() << std::endl;
  print_map<std::map<int, std::string> >(m);

  my_m.insert(ft::make_pair(4, "4"));
  my_m.insert(ft::make_pair(3, "3"));
  my_m.insert(ft::make_pair(1, "1"));
  my_m.insert(ft::make_pair(2, "2"));

  ft::pair<ft::map<int, std::string>::iterator, bool> p2 =
          my_m.insert(ft::make_pair(2, "2"));
  if (!p2.second) {
    p2.first->second = "hi";
  }

  std::cout << "my__map: "
            << "size: " << my_m.size() << std::endl;
  print_map<ft::map<int, std::string> >(my_m);
  std::cout << std::endl;
}

void map_modifier_insert_2() {
  std::cout << "[ map_modifier_insert_2 ]" << std::endl;
  std::cout << "--------------------------" << std::endl;

  std::map<int, std::string> m2;
  ft::map<int, std::string> my_m2;

  m2.insert(std::make_pair(5, "4"));
  m2.insert(std::make_pair(4, "3"));
  m2.insert(std::make_pair(2, "1"));
  m2.insert(std::make_pair(3, "2"));
  std::map<int, std::string>::iterator it = ++m2.begin();
  std::map<int, std::string>::iterator p =
          m2.insert(it, std::make_pair(5, "2"));

  std::cout << "std_map: "
            << "size: " << m2.size() << std::endl;
  print_map<std::map<int, std::string> >(m2);
  std::cout << "iter: " << p->first << " " << p->second << std::endl;
  std::cout << std::endl;

  my_m2.insert(ft::make_pair(5, "4"));
  my_m2.insert(ft::make_pair(4, "3"));
  my_m2.insert(ft::make_pair(2, "1"));
  my_m2.insert(ft::make_pair(3, "2"));
  ft::map<int, std::string>::iterator it2 = ++my_m2.begin();
  ft::map<int, std::string>::iterator p2 =
          my_m2.insert(it2, ft::make_pair(5, "2"));

  std::cout << "my__map: "
            << "size: " << my_m2.size() << std::endl;
  print_map<ft::map<int, std::string> >(my_m2);
  std::cout << "iter: " << p2->first << " " << p2->second << std::endl;
  std::cout << std::endl;
}

void map_modifier_insert_3() {
  std::cout << "[ map_modifier_insert_3 ]" << std::endl;
  std::cout << "--------------------------" << std::endl;

  std::map<int, std::string> m2;

  m2.insert(std::make_pair(1, "1"));
  m2.insert(std::make_pair(2, "2"));

  std::vector<std::pair<int, std::string> > v;

  v.push_back(std::make_pair(3, "3"));
  v.push_back(std::make_pair(4, "3"));
  v.push_back(std::make_pair(5, "3"));

  m2.insert(v.begin(), v.end());

  std::cout << "std_map: "
            << "size: " << m2.size() << std::endl;
  print_map<std::map<int, std::string> >(m2);
  std::cout << std::endl;

  ft::map<int, std::string> my_m2;
  my_m2.insert(ft::make_pair(1, "1"));
  my_m2.insert(ft::make_pair(2, "2"));

  ft::vector<ft::pair<int, std::string> > my_v;

  my_v.push_back(ft::make_pair(3, "3"));
  my_v.push_back(ft::make_pair(4, "3"));
  my_v.push_back(ft::make_pair(5, "3"));

  my_m2.insert(my_v.begin(), my_v.end());

  std::cout << "my__map: "
            << "size: " << my_m2.size() << std::endl;
  print_map<ft::map<int, std::string> >(my_m2);
  std::cout << std::endl;
}

void map_modifier_insert() {
  map_modifier_insert_1();
  map_modifier_insert_2();
  map_modifier_insert_3();
}

void map_modifiers() { map_modifier_insert(); }

void map_capacity() {
  std::cout << "[ map_capacity ]" << std::endl;
  std::cout << "--------------------------" << std::endl;

  std::map<int, std::string> m;

  m.insert(std::make_pair(1, "1"));
  m.insert(std::make_pair(2, "2"));

  std::cout << "std_map: "
            << "max_size: " << m.max_size() << ", empty: " << m.empty()
            << std::endl;
  print_map<std::map<int, std::string> >(m);
  std::cout << std::endl;

  ft::map<int, std::string> my_m;
  my_m.insert(ft::make_pair(1, "1"));
  my_m.insert(ft::make_pair(2, "2"));

  std::cout << "my__map: "
            << "max_size: " << my_m.max_size() << ", empty: " << my_m.empty()
            << std::endl;
  print_map<ft::map<int, std::string> >(my_m);
  std::cout << std::endl;
}

void map_equal_oper() {
  std::cout << "[ map_equal_oper ]" << std::endl;
  std::cout << "--------------------------" << std::endl;

  std::map<int, std::string> m;

  m.insert(std::make_pair(1, "1"));
  m.insert(std::make_pair(2, "2"));
  m.insert(std::make_pair(3, "3"));
  m.insert(std::make_pair(4, "4"));
  m.insert(std::make_pair(5, "5"));

  std::map<int, std::string> m2;
  m2 = m;

  std::cout << "std_map: "
            << "size: " << m2.size() << ", empty: " << m2.empty()
            << std::endl;
  print_map<std::map<int, std::string> >(m2);
  std::cout << std::endl;

  ft::map<int, std::string> my_m;

  my_m.insert(ft::make_pair(1, "1"));
  my_m.insert(ft::make_pair(2, "2"));
  my_m.insert(ft::make_pair(3, "3"));
  my_m.insert(ft::make_pair(4, "4"));
  my_m.insert(ft::make_pair(5, "5"));

  ft::map<int, std::string> my_m2;
  my_m2 = my_m;

  std::cout << "my__map: "
            << "size: " << my_m2.size() << ", empty: " << my_m2.empty()
            << std::endl;
  print_map<ft::map<int, std::string> >(my_m2);
  std::cout << std::endl;
}

void map_rev_iter(){
  std::cout << "[ map_rev_iter ]" << std::endl;
  std::cout << "--------------------------" << std::endl;
  ft::map<int, std::string> m;
  m.insert(ft::make_pair(1, "1"));
  m.insert(ft::make_pair(2, "2"));
  m.insert(ft::make_pair(3, "3"));
  m.insert(ft::make_pair(4, "4"));
  m.insert(ft::make_pair(5, "5"));

  for (ft::map<int, std::string>::reverse_iterator it = m.rbegin(); it != m.rend(); ++it)
    std::cout << it->first << " ";
  std::cout << std::endl;
}

void map_big_oper(){
  std::cout << "[ map_big_oper ]" << std::endl;
  std::cout << "--------------------------" << std::endl;

  std::map<int, std::string> m;
  m.insert(std::make_pair(1, "1"));
  m.insert(std::make_pair(2, "2"));
  m.insert(std::make_pair(3, "3"));
  m.insert(std::make_pair(4, "4"));
  m.insert(std::make_pair(5, "5"));
  m[3] = 97;
  m[6] = 98;
  for (std::map<int, std::string>::iterator it = m.begin(); it != m.end(); ++it)
    std::cout << it->first << " " << it->second << ", ";
  std::cout << std::endl;

  ft::map<int, std::string> my_m;
  my_m.insert(ft::make_pair(1, "1"));
  my_m.insert(ft::make_pair(2, "2"));
  my_m.insert(ft::make_pair(3, "3"));
  my_m.insert(ft::make_pair(4, "4"));
  my_m.insert(ft::make_pair(5, "5"));
  my_m[3] = 97;
  my_m[6] = 98;
  for (ft::map<int, std::string>::iterator it = my_m.begin(); it != my_m.end(); ++it)
    std::cout << it->first << " " << it->second << ", ";
  std::cout << std::endl;


}