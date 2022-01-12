#ifndef SHRUBBERYCREATIONFORM_HPP
#define SHRUBBERYCREATIONFORM_HPP
#include <fstream>

#include "Form.hpp"

class ShrubberyCreationForm : public Form {
 private:
 public:
  ShrubberyCreationForm(const std::string target);
  ShrubberyCreationForm(const ShrubberyCreationForm& obj);
  ~ShrubberyCreationForm();
  ShrubberyCreationForm& operator=(const ShrubberyCreationForm& obj);
  void execute(const Bureaucrat& executor) const;
  static Form* create(const std::string target);
};

#endif
