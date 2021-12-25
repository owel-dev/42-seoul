#include "Zombie.hpp"

int main(void) {
  Zombie *zombie1 = newZombie("ulee");
  zombie1->announce();
  randomChump("hello");
  delete zombie1;

  return (0);
}