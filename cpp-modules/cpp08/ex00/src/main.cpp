
#include "Easyfind.hpp"

int main() {
  int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  try {
    std::vector<int> vec(arr, arr + sizeof(arr) / sizeof(int));
    std::cout << "[ vector ]" << std::endl;
    for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
      std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::vector<int>::iterator it = easyfind(vec, 5);
    if (it == vec.end())
      throw NotFoundException();
    else
      std::cout << "find " << *it << std::endl;

    std::cout << std::endl;

    std::cout << "[ list ]" << std::endl;
    std::list<int> li(arr, arr + sizeof(arr) / sizeof(int));
    for (std::list<int>::iterator it = li.begin(); it != li.end(); ++it) {
      std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::list<int>::iterator it2 = easyfind(li, 42);
    if (it2 == li.end())
      throw NotFoundException();
    else
      std::cout << "find " << *it2 << std::endl;
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }
}