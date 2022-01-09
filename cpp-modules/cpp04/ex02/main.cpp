#include <iostream>

#include "Animal.hpp"
#include "Brain.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

int main() {
  Cat a("one");
  std::cout << "A.Brain address: " << &a.getBrain() << std::endl;
  Cat c;
  c.printBrain();

  c = a;
  a.printBrain();
  std::cout << std::endl;
  c.printBrain();

  std::cout << "A.Brain address: " << &a.getBrain() << std::endl;
  std::cout << "C.Brain address: " << &c.getBrain() << std::endl;
}
