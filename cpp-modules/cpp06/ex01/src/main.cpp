#include <iostream>

#include "Data.hpp"

int main() {
  struct Data data;
  data.name = "ulee";
  data.num = 1;

  uintptr_t temp = serialize(&data);
  Data *temp2 = deserialize(temp);
  std::cout << "name: " << temp2->name << " num: " << temp2->num << std::endl;
}