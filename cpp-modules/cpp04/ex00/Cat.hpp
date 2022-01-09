#ifndef CAT_HPP
#define CAT_HPP
#include "Animal.hpp"

class Cat : public Animal {
 private:
 public:
  Cat();
  Cat(const Cat& obj);
  ~Cat();
  void makeSound(void) const;
  Cat& operator=(const Cat& obj);
};

#endif