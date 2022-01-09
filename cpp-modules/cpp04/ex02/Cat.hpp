#ifndef CAT_HPP
#define CAT_HPP
#include "Animal.hpp"
#include "Brain.hpp"

class Cat : public Animal {
 private:
  Brain* brain;

 public:
  Cat();
  Cat(const Cat& obj);
  Cat(std::string str);
  ~Cat();
  void makeSound(void) const;
  Cat& operator=(const Cat& obj);
  void printBrain(void) const;
  const Brain& getBrain(void) const;
};

#endif