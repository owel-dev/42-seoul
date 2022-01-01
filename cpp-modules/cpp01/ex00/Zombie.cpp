/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 12:22:38 by ulee              #+#    #+#             */
/*   Updated: 2021/12/27 17:26:26 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
Zombie::Zombie() {}
Zombie::~Zombie() { std::cout << "Zombie Destructor called\n"; }

void Zombie::setName(std::string name) { this->zombie_name = name; }
std::string Zombie::getName() { return (this->zombie_name); }

void Zombie::announce(void) {
  std::cout << '<' << this->getName() << "> "
            << "BraiiiiiiinnnzzzZ..." << '\n';
}
