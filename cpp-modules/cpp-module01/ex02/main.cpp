/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 12:22:54 by ulee              #+#    #+#             */
/*   Updated: 2021/12/26 12:22:55 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int main(void) {
  std::string str = "HI THIS IS BRAIN";
  std::string *stringPTR = &str;
  std::string &stringREF = str;

  std::cout << "str: HI THIS IS BRAIN"
            << "\n\n";

  std::cout << "&str: " << &str << '\n'
            << "stringPTR: " << stringPTR << '\n'
            << "&stringREF: " << &stringREF << "\n\n";

  std::cout << "str: " << str << '\n'
            << "*stringPTR: " << *stringPTR << '\n'
            << "stringREF: " << stringREF << '\n';

  return (0);
}