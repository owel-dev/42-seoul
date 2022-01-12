#include "PresidentialPardonForm.hpp"

#include "Bureaucrat.hpp"

PresidentialPardonForm::PresidentialPardonForm(const std::string target)
    : Form("PresidentialPardon", 25, 5, target) {}

PresidentialPardonForm::PresidentialPardonForm(
    const PresidentialPardonForm& obj)
    : Form(obj) {}

PresidentialPardonForm::~PresidentialPardonForm() {}

PresidentialPardonForm& PresidentialPardonForm::operator=(
    const PresidentialPardonForm& obj) {
  this->Form::operator=(obj);
  return (*this);
}

void PresidentialPardonForm::execute(const Bureaucrat& executor) const {
  this->checkForm(executor);
  std::cout << this->getTarget() << " has been pardoned by "
            << executor.getName() << std::endl;
}

Form* PresidentialPardonForm::create(const std::string target) {
  return (new PresidentialPardonForm(target));
}