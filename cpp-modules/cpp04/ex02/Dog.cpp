#include "Dog.hpp"

Dog::Dog() : Animal("Dog") {
  std::cout << "Dog constructor call" << std::endl;
  this->brain = new Brain();
}

Dog::Dog(const Dog& obj) : Animal(obj) {
  std::cout << "Dog copy constructor call" << std::endl;
  this->brain = new Brain(*(obj.brain));
}

Dog::Dog(std::string str) : Animal("Cat") {
  std::cout << "Dog constructor call" << std::endl;
  this->brain = new Brain(str);
}

Dog::~Dog() {
  delete this->brain;
  std::cout << "Dog distructor call" << std::endl;
}

void Dog::makeSound(void) const { std::cout << "Dog make sound!" << std::endl; }

Dog& Dog::operator=(const Dog& obj) {
  std::cout << "Dog assign operator call" << std::endl;
  this->type = obj.getType();
  delete this->brain;
  this->brain = new Brain(*(obj.brain));
  return (*this);
}

void Dog::printBrain(void) const { this->brain->printIdeas(); }

const Brain& Dog::getBrain(void) const { return (*this->brain); }
