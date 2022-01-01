/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 12:23:16 by ulee              #+#    #+#             */
/*   Updated: 2021/12/27 20:21:02 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon(std::string weapon) { this->type = weapon; }

const std::string &Weapon::getType(void) { return (this->type); }

void Weapon::setType(std::string type) { this->type = type; }