#include "Scalar.hpp"

Scalar::Scalar(const char* str) : str(std::string(str)) {}

Scalar::Scalar(const Scalar& obj) { *this = obj; }

Scalar::~Scalar() {}

Scalar& Scalar::operator=(const Scalar& obj) {
  if (this == &obj) return (*this);
  return (*this);
}

void Scalar::ConvertChar(void) const {
  int num;

  std::cout << "char: ";
  try {
    num = std::stoi(this->str);
    if (255 < num || num < 0) throw ImpossibleExeption();
    if (!isprint(num)) throw NonDisplaybleException();
    std::cout << static_cast<char>(num);
  } catch (NonDisplaybleException& e) {
    std::cerr << "Non displayable";
  } catch (...) {
    std::cerr << "impossible";
  }
}

void Scalar::ConvertInt(void) const {
  int num;

  std::cout << "int: ";
  try {
    num = std::stoi(this->str);
    std::cout << num;
  } catch (...) {
    std::cerr << "impossible";
  }
}

void Scalar::ConvertFloat(void) const {
  float num;

  std::cout << "float: ";
  try {
    num = std::stof(this->str);
    std::cout << num;
    if (num - (int)num == 0) std::cout << ".0";
    std::cout << "f";
  } catch (...) {
    std::cerr << "impossible";
  }
}

void Scalar::ConvertDouble(void) const {
  double num;

  std::cout << "double: ";
  try {
    num = std::stod(this->str);
    std::cout << num;
    if (num - (int)num == 0) std::cout << ".0";
  } catch (...) {
    std::cerr << "impossible";
  }
}

std::ostream& operator<<(std::ostream& stream, const Scalar& obj) {
  obj.ConvertChar();
  std::cout << std::endl;
  obj.ConvertInt();
  std::cout << std::endl;
  obj.ConvertFloat();
  std::cout << std::endl;
  obj.ConvertDouble();
  return (stream);
}
