#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include <iomanip>
#include <iostream>
#include <string>

#include "Contact.hpp"

class Phonebook {
 private:
  Contact contact[8];
  int amount;
  int add_count;
  // int d;
 public:
  Phonebook();
  ~Phonebook();
  void add(void);
  void search(void);
  void secret(void);
  void printHeader(void);
  void printAllFileds(void);
};

#endif