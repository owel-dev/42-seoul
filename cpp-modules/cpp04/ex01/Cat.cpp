#include "Cat.hpp"

Cat::Cat() : Animal("Cat") {
  std::cout << "Cat constructor call" << std::endl;
  this->brain = new Brain();
}

Cat::Cat(std::string str) : Animal("Cat") {
  std::cout << "Cat constructor call" << std::endl;
  this->brain = new Brain(str);
}

Cat::Cat(const Cat& obj) : Animal(obj) {
  std::cout << "Cat copy constructor call" << std::endl;
  this->brain = new Brain(*(obj.brain));
}

Cat::~Cat() {
  delete this->brain;
  std::cout << "Cat distructor call" << std::endl;
}

void Cat::makeSound(void) const { std::cout << "Cat make sound!" << std::endl; }

Cat& Cat::operator=(const Cat& obj) {
  std::cout << "Cat assign operator call" << std::endl;
  this->Animal::operator=(obj);
  delete this->brain;
  this->brain = new Brain(*(obj.brain));
  return (*this);
}

void Cat::printBrain(void) const { this->brain->printIdeas(); }

const Brain& Cat::getBrain(void) const { return (*this->brain); }