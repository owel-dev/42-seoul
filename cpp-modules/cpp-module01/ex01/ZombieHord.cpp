/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ZombieHord.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 12:22:52 by ulee              #+#    #+#             */
/*   Updated: 2021/12/26 12:22:53 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie *zombieHorde(int N, std::string name) {
  Zombie *horde;

  horde = new Zombie[N];
  for (int i = 0; i < N; i++) horde[i].setName(name);
  for (int i = 0; i < N; i++) horde[i].announce();
  return (horde);
}
