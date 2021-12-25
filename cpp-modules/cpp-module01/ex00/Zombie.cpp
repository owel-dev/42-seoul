#include "Zombie.hpp"

Zombie::~Zombie() { std::cout << "Zombie Destructor called\n"; }

void Zombie::setName(std::string name) { this->zombie_name = name; }
std::string Zombie::getName() { return (this->zombie_name); }

void Zombie::announce(void) {
  std::cout << '<' << this->zombie_name << "> "
            << "BraiiiiiiinnnzzzZ..." << '\n';
}
