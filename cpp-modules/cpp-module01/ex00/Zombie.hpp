/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 12:22:40 by ulee              #+#    #+#             */
/*   Updated: 2021/12/27 17:25:55 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <iostream>

class Zombie {
 private:
  std::string zombie_name;

 public:
  Zombie();
  ~Zombie();

  void setName(std::string);
  std::string getName(void);

  void announce(void);
};

Zombie *newZombie(std::string name);
void randomChump(std::string name);

#endif