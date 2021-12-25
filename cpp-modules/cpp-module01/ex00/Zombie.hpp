#include <iostream>

class Zombie {
 private:
  std::string zombie_name;

 public:
  ~Zombie();

  void setName(std::string);
  std::string getName(void);

  void announce(void);
};

Zombie *newZombie(std::string name);
void randomChump(std::string name);