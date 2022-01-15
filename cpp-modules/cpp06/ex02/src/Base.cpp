#include "Base.hpp"

Base::Base() {}
Base::Base(const Base& obj) { *this = obj; }
Base::~Base() {}
Base& Base::operator=(const Base& obj) {
  (void)obj;
  return *this;
}