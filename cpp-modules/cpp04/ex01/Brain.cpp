#include "Brain.hpp"

Brain::Brain() {
  for (int i = 0; i < SIZE; i++) this->ideas[i] = "default";
  std::cout << "Brain constructor call" << std::endl;
}

Brain::Brain(std::string str) {
  for (int i = 0; i < SIZE; i++) this->ideas[i] = str;
  std::cout << "Brain constructor call" << std::endl;
}

Brain::Brain(const Brain& obj) {
  std::cout << "Brain copy constructor call" << std::endl;
  for (int i = 0; i < SIZE; i++) this->ideas[i] = obj.ideas[i];
}

Brain::~Brain() { std::cout << "Brain distructor call" << std::endl; }

Brain& Brain::operator=(const Brain& obj) {
  std::cout << "Brain assign operator call" << std::endl;
  for (int i = 0; i < SIZE; i++) this->ideas[i] = obj.ideas[i];
  return (*this);
}

void Brain::printIdeas(void) const {
  for (int i = 0; i < SIZE; i++) std::cout << this->ideas[i] << std::endl;
}
