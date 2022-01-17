#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP
// #include <algorithm>
#include <iostream>
#include <stack>

template <typename T>
class MutantStack : public std::stack<T> {
 private:
 public:
  MutantStack() : MutantStack::stack(){};
  MutantStack(const MutantStack& obj) : MutantStack::stack(obj){};
  ~MutantStack(){};
  MutantStack& operator=(const MutantStack& obj) {
    if (this != &obj) MutantStack::stack::operator=(obj);
    return (*this);
  };

  typedef typename MutantStack::stack::container_type::iterator iterator;
  iterator begin() { return (this->c.begin()); };
  iterator end() { return (this->c.end()); };

  typedef typename MutantStack::stack::container_type::const_iterator
      const_iterator;
  const_iterator cbegin() const { return (this->c.cbegin()); };
  const_iterator cend() const { return (this->c.cend()); };

  typedef typename MutantStack::stack::container_type::reverse_iterator
      reverse_iterator;
  reverse_iterator rbegin() { return (this->c.rbegin()); };
  reverse_iterator rend() { return (this->c.rend()); };

  typedef typename MutantStack::stack::container_type::const_reverse_iterator
      const_reverse_iterator;
  const_reverse_iterator crbegin() const { return (this->c.crbegin()); };
  const_reverse_iterator crend() const { return (this->c.crend()); };
};

#endif