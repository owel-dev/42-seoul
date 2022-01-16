#ifndef ARRAY_HPP
#define ARRAY_HPP
#include <iostream>

template <typename T>
class Array {
 private:
  T* array;
  unsigned int length;

 public:
  Array();
  Array(const unsigned int n);
  Array(const Array& obj);
  ~Array();

  Array& operator=(const Array& obj);
  T& operator[](const int n);

  unsigned int size(void) const;
};

class outOfIndex : public std::exception {
 public:
  const char* what() const throw() { return ("Throw outOfIndex!"); }
};

#endif
