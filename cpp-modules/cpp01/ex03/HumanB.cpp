/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 12:23:04 by ulee              #+#    #+#             */
/*   Updated: 2021/12/26 16:56:40 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"

HumanB::HumanB(std::string name) { this->name = name; }

void HumanB::setWeapon(Weapon &weapon) { this->weapon = &weapon; }

void HumanB::attack(void) {
  std::cout << this->name << " attacks with his " << this->weapon->getType()
            << '\n';
}