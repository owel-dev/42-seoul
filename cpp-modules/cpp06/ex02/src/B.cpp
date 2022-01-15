#include "B.hpp"

B::B() {}
B::B(const B& obj) : Base(obj) {}
B::~B() {}
B& B::operator=(const B& obj) {
  (void)obj;
  return (*this);
}