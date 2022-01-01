/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 20:09:48 by ulee              #+#    #+#             */
/*   Updated: 2021/12/25 00:38:34 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Phonebook.hpp"

int main() {
  Phonebook phonebook;
  std::string input;

  while (true) {
    std::cout << "Please input: [ add | search | exit | secret ] > ";
    std::getline(std::cin, input);
    if (input == "exit") return 0;
    if (input == "add") phonebook.add();
    if (input == "search") phonebook.search();
    if (input == "secret") phonebook.secret();
  }
  return 0;
}
