#include "MyException.hpp"

const char* ImpossibleExeption::what() const throw() {
  return "Throw ImpossibleExeption!";
}
const char* NonDisplaybleException::what() const throw() {
  return "Throw NonDisplaybleException!";
}
