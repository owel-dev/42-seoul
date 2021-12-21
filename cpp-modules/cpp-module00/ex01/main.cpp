/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 20:09:48 by ulee              #+#    #+#             */
/*   Updated: 2021/12/21 20:45:45 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Phonebook.hpp"

int main(int argc, char const *argv[])
{
    Phonebook phonebook;
    std::string input;
    
    std::cout << "Please input: [ ADD | SEARCH | EXIT ] > ";
    std::cin >> input;
    if (input == "EXIT")
        return 0;
    if (input == "ADD")
        phonebook.add();
    if (input == "SEARCH")
        phonebook.add();

    return 0;
}
