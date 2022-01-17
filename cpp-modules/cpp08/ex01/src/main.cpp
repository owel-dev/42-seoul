#include "span.hpp"

int main() {
  // add 10000
  std::vector<int> vec;
  for (size_t i = 0; i < 10000; i++) {
    vec.push_back(i);
  }
  span s(10000);
  s.addNumber(vec.begin(), vec.end());
  s.printElements();
  std::cout << "longest: " << s.longestSpan()
            << ", shortest: " << s.shortestSpan() << std::endl;

  // exception test - addNumber())
  try {
    s.addNumber(10001);
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }

  // exception test - longestSpan()
  span s2(1);
  s2.addNumber(1);
  try {
    std::cout << "longest: " << s2.longestSpan() << std::endl;
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }

  // subject main test
  span sp = span(5);
  sp.addNumber(5);
  sp.addNumber(3);
  sp.addNumber(17);
  sp.addNumber(9);
  sp.addNumber(11);
  std::cout << sp.shortestSpan() << std::endl;
  std::cout << sp.longestSpan() << std::endl;
}
