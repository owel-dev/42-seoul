#ifndef SCALAR_HPP
#define SCALAR_HPP
#include <iostream>
#include <string>

#include "MyException.hpp"

class Scalar {
 private:
  const std::string str;

 public:
  Scalar(const char* str);
  Scalar(const Scalar& obj);
  ~Scalar();
  Scalar& operator=(const Scalar& obj);
  void ConvertChar(void) const;
  void ConvertInt(void) const;
  void ConvertFloat(void) const;
  void ConvertDouble(void) const;
};
std::ostream& operator<<(std::ostream& stream, const Scalar& obj);

#endif
