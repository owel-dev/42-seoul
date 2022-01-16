#include "Array.hpp"

template <typename T>
Array<T>::Array() : array(0), length(0) {}

template <typename T>
Array<T>::Array(const unsigned int n) {
  if (n == 0) {
    Array();
    return;
  }
  this->array = new T[n];
  this->length = n;
  for (size_t i = 0; i < n; i++) {
    this->array[i] = 0;
  }
}

template <typename T>
Array<T>::Array(const Array<T>& obj) : length(obj.length) {
  this->array = new T[obj.length];
  for (size_t i = 0; i < length; i++) {
    this->array[i] = obj.array[i];
  }
}

template <typename T>
Array<T>::~Array() {
  delete[] this->array;
}

template <typename T>
Array<T>& Array<T>::operator=(const Array<T>& obj) {
  if (this == &obj) return (*this);
  if (this->length != 0) delete[] this->array;
  this->array = new T[obj.length];
  this->length = obj.length;
  for (size_t i = 0; i < obj.length; i++) {
    this->array[i] = obj.array[i];
  }
  return (*this);
}

template <typename T>
T& Array<T>::operator[](const int n) {
  if (0 > n || n >= static_cast<int>(this->length)) throw outOfIndex();
  return (this->array[n]);
}

template <typename T>
unsigned int Array<T>::size(void) const {
  return (this->length);
}
