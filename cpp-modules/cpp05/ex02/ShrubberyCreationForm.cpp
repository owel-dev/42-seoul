#include "ShrubberyCreationForm.hpp"

#include <sstream>

#include "Bureaucrat.hpp"
#include "GradeException.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(const std::string target)
    : Form("ShrubberyCreation", 145, 137, target) {}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& obj)
    : Form(obj) {}

ShrubberyCreationForm::~ShrubberyCreationForm() {}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(
    const ShrubberyCreationForm& obj) {
  this->Form::operator=(obj);
  return (*this);
}

void ShrubberyCreationForm::execute(Bureaucrat const& executor) const {
  this->checkForm(executor);
  std::ifstream open_file("tree.txt");
  if (!open_file.is_open()) throw std::ifstream::failure("i-file is not open");

  std::ofstream write_file(this->getTarget() + "_shrubbery", std::ios::trunc);
  if (!write_file.is_open()) throw std::ofstream::failure("o-file is not open");

  std::string s;
  open_file.seekg(0, std::ios::end);
  int size = open_file.tellg();
  s.resize(size);
  open_file.seekg(0, std::ios::beg);
  open_file.read(&s[0], size);
  write_file << s << std::endl;
}
