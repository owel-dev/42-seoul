/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Phonebook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 20:40:33 by ulee              #+#    #+#             */
/*   Updated: 2021/12/25 19:05:40 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Phonebook.hpp"

Phonebook::Phonebook() {
  amount = 0;
  add_count = 0;
}

Phonebook::~Phonebook() {}

void Phonebook::add(void) {
  this->contact[this->add_count % 8].setFields();
  if (this->amount < 8) this->amount++;
  this->add_count++;
}

void Phonebook::printHeader(void) {
  std::cout << "\n   index   first_name last_name  nick_name  phone_number "
               "#darkest_secret"
            << "\n";
  std::cout << "-------------------------------------------------------------"
            << "\n";
}

void Phonebook::printAllFileds(void) {
  for (int i = 0; i < this->amount; i++) {
    std::cout << std::setw(10) << i << '|';
    this->contact[i].printField();
    std::cout << "\n";
  }
}

void Phonebook::search(void) {
  std::string input;
  int index;

  printHeader();
  printAllFileds();
  while (true) {
    std::cout << "input [ index | exit ]> ";
    std::getline(std::cin, input);
    if (input == "exit") return;
    try {
      index = std::stoi(input);
    } catch (const std::exception& e) {
      std::cerr << "Index can only be a number."
                << "\n";
      continue;
    }
    if (0 <= index && index < this->amount) {
      printHeader();
      this->contact[index].printField();
    } else {
      std::cout << "Please enter an index in the correct range. Current number "
                   "of contacts: "
                << this->amount;
    }
    std::cout << "\n";
  }
}

void Phonebook::secret(void) {
  std::string input;
  int index;

  while (true) {
    std::cout << "==Secret Mode== input [ index | exit ]> ";
    std::getline(std::cin, input);
    if (input == "exit") return;
    try {
      index = std::stoi(input);
    } catch (const std::exception& e) {
      std::cerr << "index is only number"
                << "\n";
      continue;
    }
    if (0 <= index && index < this->amount) {
      this->contact[index].printSecret();
    } else {
      std::cout << "Please enter an index in the correct range. Current number "
                   "of contacts: "
                << this->amount;
    }
    std::cout << "\n";
  }
}
