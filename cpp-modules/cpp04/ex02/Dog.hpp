#ifndef DOG_HPP
#define DOG_HPP
#include "Animal.hpp"
#include "Brain.hpp"

class Dog : public Animal {
 private:
  Brain* brain;

 public:
  Dog();
  Dog(const Dog& obj);
  Dog(std::string str);
  ~Dog();
  void makeSound(void) const;
  Dog& operator=(const Dog& obj);
  void printBrain(void) const;
  const Brain& getBrain(void) const;
};

#endif