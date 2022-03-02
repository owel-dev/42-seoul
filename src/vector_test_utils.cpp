#include <iterator>
#include <vector>

#include "vector.hpp"

template <class T>
void print_vector(T& v) {
  for (typename T::iterator it = v.begin(); it != v.end(); ++it)
    std::cout << *it << " ";
  std::cout << std::endl;
}