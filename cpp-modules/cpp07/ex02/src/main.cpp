#include <iostream>

#include "Array.cpp"
#include "Array.hpp"

template <>
Array<std::string>::Array(const unsigned int n) {
  if (n == 0) {
    Array();
    return;
  }
  this->array = new std::string[n];
  this->length = n;
  for (size_t i = 0; i < n; i++) {
    this->array[i] = "";
  }
}

int main() {
  try {
    Array<int> a(5);
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;
    a[3] = 4;
    a[4] = 5;

    for (size_t i = 0; i < a.size(); i++) {
      std::cout << a[i] << std::endl;
    }

    std::cout << std::endl;

    Array<std::string> str(5);
    str[0] = "zero";
    str[1] = "one";
    str[2] = "two";
    str[3] = "three";
    str[4] = "four";

    for (size_t i = 0; i < str.size(); i++) {
      std::cout << str[i] << std::endl;
    }

    std::cout << std::endl;

    Array<std::string> str2(5);
    str2[0] = "a";
    str2[1] = "b";
    str2[2] = "c";
    str2[3] = "d";
    str2[4] = "e";

    str = str2;

    for (size_t i = 0; i < str.size(); i++) {
      std::cout << str[i] << std::endl;
    }

    std::cout << std::endl;

    Array<std::string> str3(str2);
    for (size_t i = 0; i < str3.size(); i++) {
      std::cout << str3[i] << std::endl;
    }
    std::cout << str[5] << std::endl;

  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }
}