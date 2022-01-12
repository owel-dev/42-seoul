#include "GradeException.hpp"

const char* GradeTooHighException::what() const throw() {
  return ("Throw GradeTooHighException!");
}

const char* GradeTooLowException::what() const throw() {
  return ("Throw GradeTooLowException!");
}
