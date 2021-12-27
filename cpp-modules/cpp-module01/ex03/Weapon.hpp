/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 12:23:19 by ulee              #+#    #+#             */
/*   Updated: 2021/12/26 16:55:23 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <iostream>
#include <string>

// #include "HumanA.hpp"
// #include "HumanB.hpp"

class Weapon {
 private:
  std::string type;

 public:
  Weapon(std::string);
  std::string getType(void);
  void setType(std::string type);
};

#endif