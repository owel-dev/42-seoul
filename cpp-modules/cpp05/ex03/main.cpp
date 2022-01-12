#include <iostream>

#include "Bureaucrat.hpp"
#include "Form.hpp"
#include "GradeException.hpp"
#include "Intern.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

const std::string test_form[4] = {"ShrubberyCreationForm",
                                  "RobotomyRequestForm",
                                  "PresidentialPardonForm", "unknown"};

int main() {
  try {
    Bureaucrat power_man("power_man", 1);
    Intern intern;
    Form* form;

    for (int i = 0; i < 4; i++) {
      form = intern.makeForm(test_form[i], "guest");
      power_man.signForm(*form);
      power_man.executeForm(*form);
      std::cout << std::endl;
    }
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }
}