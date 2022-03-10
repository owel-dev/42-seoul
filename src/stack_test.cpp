#include "stack.hpp"

#include <iostream>
#include <iterator>
#include <memory>
#include <stack>
#include <utility>
#include <vector>

void stack_member_functions() {
  std::stack<int> st;
  ft::stack<int> my_st;

  std::cout << "[ stack_member_functions ]" << std::endl;
  std::cout << "--------------------------" << std::endl;

  st.push(1);
  st.push(2);
  st.push(3);

  my_st.push(1);
  my_st.push(2);
  my_st.push(3);

  std::cout << "std_stack: "
            << "empty: " << st.size() << " top: " << st.top()
            << " size: " << st.top() << std::endl;

  std::cout << "my__stack: "
            << "empty: " << my_st.size() << " top: " << my_st.top()
            << " size: " << my_st.top() << std::endl;

  st.pop();
  st.pop();

  my_st.pop();
  my_st.pop();

  std::cout << "std_stack: "
            << "empty: " << st.size() << " top: " << st.top()
            << " size: " << st.top() << std::endl;

  std::cout << "my__stack: "
            << "empty: " << my_st.size() << " top: " << my_st.top()
            << " size: " << my_st.top() << std::endl;
  std::cout << std::endl;
}

void stack_relation_operators() {
  ft::stack<int> my_st1;
  ft::stack<int> my_st2;

  my_st1.push(1);
  my_st1.push(2);
  my_st1.push(3);

  my_st2.push(1);
  my_st2.push(2);
  my_st2.push(3);

  std::cout << "[ stack_relation_operators ]" << std::endl;
  std::cout << "----------------------------" << std::endl;
  std::cout << "st1_stack: "
            << "empty: " << my_st1.size() << " top: " << my_st1.top()
            << " size: " << my_st1.top() << std::endl;

  std::cout << "st2_stack: "
            << "empty: " << my_st2.size() << " top: " << my_st2.top()
            << " size: " << my_st2.top() << std::endl;

  std::cout << "std_vec == my_vec: " << (my_st1 == my_st2) << "\n"
            << "std_vec != my_vec: " << (my_st1 != my_st2) << "\n"
            << "std_vec <  my_vec: " << (my_st1 < my_st2) << "\n"
            << "std_vec >  my_vec: " << (my_st1 > my_st2) << "\n"
            << "std_vec <= my_vec: " << (my_st1 <= my_st2) << "\n"
            << "std_vec >= my_vec: " << (my_st1 >= my_st2) << std::endl;

  std::cout << std::endl;
}