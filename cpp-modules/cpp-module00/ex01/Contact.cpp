/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 12:20:16 by ulee              #+#    #+#             */
/*   Updated: 2021/12/25 00:38:27 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

std::string Contact::field_name[6] = {"first_name",     "last_name",
                                      "nick_name",      "phone_number",
                                      "darkest_secret", "password"};
Contact::Contact() {}
Contact::~Contact() {}

void Contact::printHeader(void) {
  std::cout << "\n   index   first_name  last_name  nick_name  darkest_secret"
            << "\n";
  std::cout << "---------------------------------------------"
            << "\n";
}

void Contact::setFields(void) {
  for (int i = FirstName; i <= DarkestSecret + 1; i++) {
    std::cout << "input [" << this->field_name[i] << "]"
              << "> ";
    std::getline(std::cin, this->field_list[i]);
  }
}

void Contact::printField() {
  for (int i = FirstName; i <= DarkestSecret; i++) {
    if (i == DarkestSecret)
      std::cout << std::setw(10) << "******  ";
    else if (this->field_list[i].length() > 10)
      std::cout << this->field_list[i].substr(0, 9) << "."
                << "|";
    else
      std::cout << std::setw(10) << this->field_list[i] << "|";
  }
  std::cout << "\n";
}

void Contact::printSecret() {
  std::string input;

  std::cout << "Please enter a password.\n";
  std::getline(std::cin, input);
  if (this->field_list[5] != input) {
    std::cout << "The password is wrong.\n";
    return;
  }
  printHeader();
  for (int i = FirstName; i <= DarkestSecret; i++) {
    if (this->field_list[i].length() > 10)
      std::cout << this->field_list[i].substr(0, 9) << "."
                << "|";
    else
      std::cout << std::setw(10) << this->field_list[i];
    if (i != DarkestSecret) std::cout << "|";
  }
  std::cout << "\n";
}
