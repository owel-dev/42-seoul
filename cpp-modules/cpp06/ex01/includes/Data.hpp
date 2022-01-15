#include <iostream>

struct Data {
  std::string name;
  int num;
};

uintptr_t serialize(Data* ptr);

Data* deserialize(uintptr_t raw);
