#ifndef DOG_HPP
#define DOG_HPP
#include "Animal.hpp"

class Dog : public Animal {
 private:
 public:
  Dog();
  Dog(const Dog& obj);
  ~Dog();
  void makeSound(void) const;
  Dog& operator=(const Dog& obj);
};

#endif