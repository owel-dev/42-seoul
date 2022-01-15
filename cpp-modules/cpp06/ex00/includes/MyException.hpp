#ifndef MYEXCEPTION_HPP
#define MYEXCEPTION_HPP
#include <iostream>

class ImpossibleExeption : std::exception {
  const char* what() const throw();
};
class NonDisplaybleException : std::exception {
  const char* what() const throw();
};

#endif
