#include <cstdlib>
#include <ctime>
#include <iostream>

#include "A.hpp"
#include "B.hpp"
#include "Base.hpp"
#include "C.hpp"

Base* generate(void) {
  switch (rand() % 3) {
    case 0:
      std::cout << "generate A" << std::endl;
      return new A();
    case 1:
      std::cout << "generate B" << std::endl;
      return new B();
    case 2:
      std::cout << "generate C" << std::endl;
      return new C();
    default:
      return NULL;
  }
}

void identify(Base* p) {
  if (dynamic_cast<A*>(p))
    std::cout << "A" << std::endl;
  else if (dynamic_cast<B*>(p))
    std::cout << "B" << std::endl;
  else if (dynamic_cast<C*>(p))
    std::cout << "C" << std::endl;
}

void identify(Base& p) {
  try {
    A& a = dynamic_cast<A&>(p);
    (void)a;
    std::cout << "A" << std::endl;
  } catch (...) {
  }
  try {
    B& b = dynamic_cast<B&>(p);
    (void)b;
    std::cout << "B" << std::endl;
  } catch (...) {
  }
  try {
    C& c = dynamic_cast<C&>(p);
    (void)c;
    std::cout << "C" << std::endl;
  } catch (...) {
  }
}

int main() {
  srand(time(NULL));
  for (int i = 0; i < 5; i++) {
    Base* base = generate();
    identify(*base);
    identify(base);
  }
}