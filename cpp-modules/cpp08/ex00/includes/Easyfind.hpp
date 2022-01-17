#ifndef EASYFIND_HPP
#define EASYFIND_HPP
#include <iostream>
#include <iterator>
#include <list>
#include <vector>

class NotFoundException : public std::exception {
 public:
  const char* what() const throw() { return "throw NotFoundException!"; }
};

template <typename T>
typename T::iterator easyfind(T& container, int num) {
  std::cout << "Try find number " << num << "....." << std::endl;
  for (typename T::iterator it = container.begin(); it != container.end();
       ++it) {
    if (*it == num) return (it);
  }
  return (container.end());
}

#endif