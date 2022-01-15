#include "C.hpp"

C::C() {}
C::C(const C& obj) : Base(obj) {}
C::~C() {}
C& C::operator=(const C& obj) {
  (void)obj;
  return (*this);
}