#ifndef BRAIN_HPP
#define BRAIN_HPP
#define SIZE 100
#include <iostream>

class Brain {
 private:
 public:
  std::string ideas[SIZE];
  Brain();
  Brain(const Brain& obj);
  Brain(std::string str);
  ~Brain();
  Brain& operator=(const Brain& obj);
  void printIdeas(void) const;
};

#endif