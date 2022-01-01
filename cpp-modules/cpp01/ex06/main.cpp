/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 13:52:33 by ulee              #+#    #+#             */
/*   Updated: 2021/12/28 13:56:57 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Karen.hpp"

int main(int ac, char** av) {
  if (ac != 2) {
    std::cerr << "Error: argument." << std::endl;
    return 1;
  }

  Karen karen;

  try {
    karen.complain(karen.filter(av[1]));
  } catch (char const* e) {
    std::cerr << "Error: " << e << '\n';
    return 1;
  }
  return 0;
}