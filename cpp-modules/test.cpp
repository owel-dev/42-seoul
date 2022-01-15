#include <iostream>

int main() {
  const int a = 10;
  // const int *a_ptr = &a;
  // int *b = const_cast<int *>(a_ptr);
  int b = int(a);
  b = 7;
  std::cout << a << std::endl;
  std::cout << b << std::endl;
}