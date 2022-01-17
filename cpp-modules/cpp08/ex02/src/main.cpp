#include "MutantStack.hpp"

int main() {
  MutantStack<int> mstack;
  mstack.push(5);
  mstack.push(17);
  std::cout << "top: " << mstack.top() << std::endl;
  mstack.pop();
  std::cout << "size: " << mstack.size() << std::endl;
  mstack.push(3);
  mstack.push(5);
  mstack.push(737);

  // iterator test
  mstack.push(0);
  MutantStack<int>::iterator it = mstack.begin();
  MutantStack<int>::iterator ite = mstack.end();
  ++it;
  --it;
  while (it != ite) {
    std::cout << *it << std::endl;
    ++it;
  }

  // stack test
  std::stack<int> s(mstack);
  s.push(3);
  s.push(5);
  s.push(737);
  std::cout << "top: " << s.top() << std::endl;
  std::cout << "size: " << s.size() << std::endl;

  // reverse_iterator test
  MutantStack<int> mstack2;
  mstack2.push(3);
  mstack2.push(5);
  mstack2.push(737);
  MutantStack<int>::reverse_iterator rit = mstack2.rbegin();
  MutantStack<int>::reverse_iterator rite = mstack2.rend();
  ++rit;
  --rit;
  while (rit != rite) {
    std::cout << *rit << std::endl;
    ++rit;
  }
  return 0;
}