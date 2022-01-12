#include <iostream>

#include "Bureaucrat.hpp"
#include "Form.hpp"
#include "GradeException.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

int main() {
  try {
    Bureaucrat power_man("power_man", 25);
    ShrubberyCreationForm berry("home2");
    RobotomyRequestForm robot("bender");
    PresidentialPardonForm pardon("guest");
    std::cout << power_man << std::endl;
    power_man.signForm(berry);
    std::cout << berry << std::endl;
    power_man.executeForm(berry);

    std::cout << std::endl;

    std::cout << power_man << std::endl;
    power_man.signForm(robot);
    std::cout << robot << std::endl;
    power_man.executeForm(robot);

    std::cout << std::endl;

    std::cout << power_man << std::endl;
    power_man.signForm(pardon);
    std::cout << robot << std::endl;
    power_man.executeForm(pardon);

  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }
}