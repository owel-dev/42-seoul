#ifndef ITER_HPP
#define ITER_HPP

template <typename T>
void iter(T* address, int length, void (*funcPtr)(T&)) {
  for (int i = 0; i < length; i++) funcPtr(address[i]);
  int a[length];
  a[0] = 1;
}

template <typename T>
void fillArr(T& element) {
  element = 42;
}

template <typename T>
void printArr(T& element) {
  std::cout << element << " ";
  std::fflush(stdout);
}
#endif
