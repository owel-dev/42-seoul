#include "Intern.hpp"

Intern::Intern() {}
Intern::Intern(const Intern& obj) { (void)obj; }
Intern::~Intern() {}
Intern& Intern::operator=(const Intern& obj) {
  (void)obj;
  return (*this);
}
Form* Intern::makeForm(const std::string form, const std::string target) {
  Form* (*func_ptr[3])(const std::string target) = {
      ShrubberyCreationForm::create, RobotomyRequestForm::create,
      PresidentialPardonForm::create};

  for (int i = 0; i < 3; i++) {
    if (form == form_name[i]) {
      std::cout << "Intern creates" << std::endl;
      return (func_ptr[i](target));
    }
  }

  throw FormNotFound();
}
