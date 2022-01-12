#include "RobotomyRequestForm.hpp"

#include <cstdlib>
#include <ctime>

RobotomyRequestForm::RobotomyRequestForm(const std::string target)
    : Form("RobotomyRequest", 72, 45, target) {}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& obj)
    : Form(obj) {}

RobotomyRequestForm::~RobotomyRequestForm() {}

RobotomyRequestForm& RobotomyRequestForm::operator=(
    const RobotomyRequestForm& obj) {
  this->Form::operator=(obj);
  return (*this);
}

void RobotomyRequestForm::execute(const Bureaucrat& executor) const {
  this->checkForm(executor);
  std::cout << "===== drill sound =====" << std::endl;
  std::srand(std::time(0));
  if (std::rand() % 2 == 0) {
    std::cout << "robotomized successfully" << std::endl;
  } else
    std::cout << "robotomized fail" << std::endl;
}
