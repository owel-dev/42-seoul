#ifndef INTERN_HPP
#define INTERN_HPP
#include <iostream>

#include "Form.hpp"
#include "GradeException.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

class Intern {
 private:
 public:
  Intern();
  Intern(const Intern& obj);
  ~Intern();
  Intern& operator=(const Intern& obj);
  Form* makeForm(const std::string form, const std::string target);
};

#endif
