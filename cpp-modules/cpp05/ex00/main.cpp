#include "Bureaucrat.hpp"

int main() {
  try {
    Bureaucrat guest0("guest0", 140);
    Bureaucrat guest1("guest1", 1);
    // guest0.increaseGrade(140);
    // guest0.decreaseGrade(10);

    std::cout << guest0 << std::endl;

  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }
}