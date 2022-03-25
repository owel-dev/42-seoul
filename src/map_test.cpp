#include "map.hpp"

#include <__tree>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <stack>
#include <utility>
#include <vector>

void map_modifier_insert()
{
    // ft::map<int, std::string> m;
    // m.insert(ft::make_pair(4, "4"));
    // m.insert(ft::make_pair(3, "3"));
    // m.insert(ft::make_pair(1, "1"));
    // m.insert(ft::make_pair(2, "2"));

    // for (ft::map<int, std::string>::iterator it = m.begin(); it != m.end(); it++)
    // {
    //     std::cout << *it << std::endl;
    // }

    std::map<int, std::string> m;
    m.insert(std::make_pair(4, "4"));
    m.insert(std::make_pair(3, "3"));
    m.insert(std::make_pair(1, "1"));
    m.insert(std::make_pair(2, "2"));

    for (std::map<int, std::string>::iterator it = m.begin(); it != m.end(); it--)
    {
        std::cout << it->first << std::endl;
    }
}