#ifndef GRADEEXCEPTION_HPP
#define GRADEEXCEPTION_HPP
#include <iostream>

class GradeTooHighException : public std::exception {
 public:
  const char* what() const throw();
};

class GradeTooLowException : public std::exception {
 public:
  const char* what() const throw();
};

class NoSignedException : public std::exception {
 public:
  const char* what() const throw();
};

class FormNotFound : public std::exception {
 public:
  const char* what() const throw();
};

#endif