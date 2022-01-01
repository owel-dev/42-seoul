/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 16:35:15 by ulee              #+#    #+#             */
/*   Updated: 2022/01/01 16:35:16 by ulee             ###   ########.fr       */
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

Fixed::Fixed(const int num) {
  std::cout << "Int constructor called" << std::endl;
  this->value = num << Fixed::bits;
}
Fixed::Fixed(const float num) {
  std::cout << "Float constructor called" << std::endl;
  this->value = (int)roundf(num * (1 << Fixed::bits));
}

Fixed::~Fixed() { std::cout << "Destructor called" << std::endl; }

Fixed &Fixed::operator=(Fixed const &obj) {
  std::cout << "Assignation operator called" << std::endl;
  this->value = obj.value;
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

float Fixed::toFloat(void) const {
  return ((float)this->value / (1 << Fixed::bits));
}

int Fixed::toInt(void) const { return (this->value >> Fixed::bits); }

std::ostream &operator<<(std::ostream &out, Fixed const &obj) {
  out << obj.toFloat();
  return (out);
}