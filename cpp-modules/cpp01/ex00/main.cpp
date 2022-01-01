/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 12:22:29 by ulee              #+#    #+#             */
/*   Updated: 2021/12/26 14:03:58 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main(void) {
  Zombie *zombie1 = newZombie("ulee");
  zombie1->announce();
  randomChump("hello");
  delete zombie1;

  return (0);
}