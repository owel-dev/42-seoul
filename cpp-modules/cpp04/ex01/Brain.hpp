#ifndef BRAIN_HPP
#define BRAIN_HPP
#define SIZE 100
#include <iostream>

class Brain {
 private:
  std::string ideas[SIZE];

 public:
  Brain();
  Brain(const Brain& obj);
  Brain(std::string str);
  ~Brain();
  Brain& operator=(const Brain& obj);
  void printIdeas(void) const;
};

#endif