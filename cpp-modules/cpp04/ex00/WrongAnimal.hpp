#ifndef WRONGANIMAL_HPP
#define WRONGANIMAL_HPP
#include <iostream>

class WrongAnimal {
 protected:
  std::string type;

 public:
  WrongAnimal();
  WrongAnimal(const std::string name);
  ~WrongAnimal();
  WrongAnimal(const WrongAnimal& obj);
  void makeSound(void) const;
  std::string getType(void) const;
  WrongAnimal& operator=(const WrongAnimal& obj);
};

#endif