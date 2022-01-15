#ifndef C_HPP
#define C_HPP
#include "Base.hpp"

class C : public Base {
 private:
 public:
  C();
  C(const C& obj);
  ~C();
  C& operator=(const C& obj);
};

#endif
