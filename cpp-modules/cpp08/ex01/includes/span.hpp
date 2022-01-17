#ifndef SPAN_HPP
#define SPAN_HPP
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <vector>

class span {
 private:
  unsigned int size;
  std::vector<int> vec;

 public:
  span(const unsigned int n);
  span(const span& obj);
  ~span();
  span& operator=(const span& obj);
  void addNumber(const int num);
  void addNumber(const std::vector<int>::iterator& begin,
                 const std::vector<int>::iterator& end);
  long shortestSpan(void) const;
  long longestSpan(void) const;
  void printElements(void) const;
};

class FullSizeException : public std::exception {
 public:
  const char* what() const throw() { return "throw FulLSizeException!"; }
};

class ShortSizeException : public std::exception {
 public:
  const char* what() const throw() { return "throw ShortSizeException!"; }
};

#endif
