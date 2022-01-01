/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 16:35:05 by ulee              #+#    #+#             */
/*   Updated: 2022/01/01 16:35:06 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed() {
  this->value = 0;
  std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const Fixed &obj) {
  std::cout << "Copy constructor called" << std::endl;
  *this = obj;
}

Fixed::~Fixed() { std::cout << "Destructor called" << std::endl; }

Fixed &Fixed::operator=(Fixed const &obj) {
  std::cout << "Assignation operator called" << std::endl;
  this->value = obj.getRawBits();
  return (*this);
}

int Fixed::getRawBits(void) const {
  std::cout << "getRawBits member function called" << std::endl;
  return (this->value);
}

void Fixed::setRawBits(int const raw) {
  std::cout << "setRawBits member function called" << std::endl;
  this->value = raw;
}
