#include "WrongCat.hpp"

WrongCat::WrongCat() : WrongAnimal("WrongCat") { std::cout << "WrongCat constructor call" << std::endl; }

WrongCat::WrongCat(const WrongCat& obj) : WrongAnimal(obj) {
  std::cout << "WrongCat copy constructor call" << std::endl;
}

WrongCat::~WrongCat() { std::cout << "WrongCat distructor call" << std::endl; }

void WrongCat::makeSound(void) const { std::cout << "WrongCat make sound!" << std::endl; }

WrongCat& WrongCat::operator=(const WrongCat& obj) {
  std::cout << "WrongCat assign operator call" << std::endl;
  this->type = obj.getType();
  return (*this);
}