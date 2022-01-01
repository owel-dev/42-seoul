/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 12:23:06 by ulee              #+#    #+#             */
/*   Updated: 2021/12/26 16:56:37 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANB_HPP
#define HUMANB_HPP
#include "Weapon.hpp"

class HumanB {
 private:
  Weapon *weapon;
  std::string name;

 public:
  HumanB(std::string name);
  void attack(void);
  void setWeapon(Weapon &weapon);
};

#endif