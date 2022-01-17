#include "span.hpp"

span::span(const unsigned int n) : size(n) {}
span::~span() {}
void span::addNumber(const int num) {
  if (size == vec.size()) throw FullSizeException();
  this->vec.push_back(num);
}

void span::addNumber(const std::vector<int>::iterator& begin,
                     const std::vector<int>::iterator& end) {
  for (std::vector<int>::iterator it = begin; it != end; ++it) {
    addNumber(*it);
  }
}

span::span(const span& obj) : size(obj.size), vec(obj.vec) {}

span& span::operator=(const span& obj) {
  this->size = obj.size;
  this->vec = obj.vec;
  return (*this);
}

long span::shortestSpan(void) const {
  if (this->size <= 1) throw ShortSizeException();

  long min;
  min = LONG_MAX;
  std::vector<int> temp = this->vec;
  std::sort(temp.begin(), temp.end());
  for (size_t i = 0; i < this->size - 1; i++) {
    int span = std::abs(temp[i + 1] - temp[i]);
    if (min > span) min = span;
  }
  return (min);
}

long span::longestSpan(void) const {
  if (this->size <= 1) throw ShortSizeException();

  std::vector<int> temp = this->vec;
  std::sort(temp.begin(), temp.end());

  return (std::abs(temp.back() - temp.front()));
}

void span::printElements(void) const {
  std::vector<int> temp = this->vec;
  for (std::vector<int>::iterator it = temp.begin(); it != temp.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}
