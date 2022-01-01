/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 12:23:02 by ulee              #+#    #+#             */
/*   Updated: 2021/12/26 16:54:58 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANA_HPP
#define HUMANA_HPP
#include "Weapon.hpp"

class HumanA {
 private:
  Weapon &weapon;
  std::string name;

 public:
  HumanA(std::string name, Weapon &weapon);
  void attack(void);
};

#endif