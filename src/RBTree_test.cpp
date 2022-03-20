#include "RBTree.hpp"

#include <iostream>

void RBTree_test()
{
    std::cout << "[   Red_black_tree test   ]" << std::endl;
    std::cout << "----------------------------" << std::endl;
    ft::rb_tree<int> rb;
    ft::rb_tree<ft::pair<int, std::string> > rb2;
    int data;

    // std::cin >> data;
    // while (data != 0) {
    //   rb.insertValue(data);
    //   rb.printTree();
    //   std::cin >> data;
    // }
    int arr[7] = {10, 5, 15, 17, 19, 21, 23};
    for (size_t i = 0; i < 7; i++) rb.insert_value(arr[i]);
    // ft::pair<int, std::string> a1(1, "1");
    // ft::pair<int, std::string> a2(2, "2");
    // ft::pair<int, std::string> a3(3, "3");
    // ft::pair<int, std::string> a4(4, "4");
    rb.delete_value(5);
    rb.print_tree();
    std::cout << std::endl;
    // rb.insert_value(a2);
    // rb.insert_value(a1);
    // rb.insert_value(a4);
    // rb.insert_value(a3);

    rb2.insert_value(ft::make_pair(10, "2"));
    rb2.insert_value(ft::make_pair(5, "1"));
    rb2.insert_value(ft::make_pair(15, "4"));
    rb2.insert_value(ft::make_pair(17, "3"));
    rb2.insert_value(ft::make_pair(19, "3"));
    rb2.insert_value(ft::make_pair(21, "3"));
    rb2.insert_value(ft::make_pair(23, "3"));
    rb2.delete_value(ft::make_pair(5, "1"));
    // ft::RBtree<std::pair<int, std::string>>
    std::cout << std::endl;
    rb2.print_tree();

    // rb.delete_tree();

    // rb.print_tree();

    // for (size_t i = 0; i < 7; i++) rb.insert_value(arr[i]);
    // rb.print_tree();
}