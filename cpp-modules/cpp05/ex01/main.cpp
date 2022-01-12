#include <iostream>

#include "Bureaucrat.hpp"
#include "GradeException.hpp"

int main() {
  try {
    Form form("form1", 15, 15);
    Bureaucrat high_man("high_man", 1);
    Bureaucrat low_man("low_man", 100);
    std::cout << form;
    high_man.signForm(form);
    low_man.signForm(form);
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }
}