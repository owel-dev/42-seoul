/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 16:35:31 by ulee              #+#    #+#             */
/*   Updated: 2022/01/01 16:35:32 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed() { this->value = 0; }

Fixed::Fixed(const Fixed &obj) { *this = obj; }

Fixed::Fixed(const int num) { this->value = num << Fixed::bits; }
Fixed::Fixed(const float num) {
  this->value = (int)roundf(num * (1 << Fixed::bits));
}

Fixed::~Fixed() {}

Fixed &Fixed::operator=(const Fixed &obj) {
  this->value = obj.getRawBits();
  return (*this);
}

int Fixed::getRawBits(void) const { return (this->value); }

void Fixed::setRawBits(const int raw) { this->value = raw; }

float Fixed::toFloat(void) const {
  return ((float)this->value / (1 << Fixed::bits));
}

int Fixed::toInt(void) const { return (this->value >> Fixed::bits); }

std::ostream &operator<<(std::ostream &out, Fixed const &obj) {
  out << obj.toFloat();
  return (out);
}

bool Fixed::operator>(const Fixed &obj) {
  return (this->getRawBits() > obj.getRawBits());
}
bool Fixed::operator<(const Fixed &obj) {
  return (this->getRawBits() < obj.getRawBits());
}
bool Fixed::operator>=(const Fixed &obj) {
  return (this->getRawBits() >= obj.getRawBits());
}
bool Fixed::operator<=(const Fixed &obj) {
  return (this->getRawBits() <= obj.getRawBits());
}
bool Fixed::operator==(const Fixed &obj) {
  return (this->getRawBits() == obj.getRawBits());
}
bool Fixed::operator!=(const Fixed &obj) {
  return (this->getRawBits() != obj.getRawBits());
}

Fixed Fixed::operator+(const Fixed &obj) {
  Fixed ret;

  ret.setRawBits(this->getRawBits() + obj.getRawBits());
  return (ret);
}
Fixed Fixed::operator-(const Fixed &obj) {
  Fixed ret;

  ret.setRawBits(this->getRawBits() - obj.getRawBits());
  return (ret);
}
Fixed Fixed::operator*(const Fixed &obj) {
  Fixed ret;

  ret.setRawBits(this->getRawBits() * obj.getRawBits() / (1 << this->bits));
  return (ret);
}
Fixed Fixed::operator/(const Fixed &obj) {
  Fixed ret;

  ret.setRawBits(this->getRawBits() / obj.getRawBits() * (1 << this->bits));
  return (ret);
}

Fixed Fixed::operator++(int) {
  Fixed ret(*this);

  operator++();
  return (ret);
}
Fixed &Fixed::operator++() {
  this->value += 1;
  return (*this);
}
Fixed Fixed::operator--(int) {
  Fixed ret(*this);

  operator--();
  return (ret);
}
Fixed &Fixed::operator--() {
  this->value -= 1;
  return (*this);
}

Fixed &Fixed::min(Fixed &one, Fixed &two) {
  if (one > two) return (two);
  return (one);
}
const Fixed &Fixed::min(const Fixed &one, const Fixed &two) {
  if ((Fixed)one > (Fixed)two) return (two);
  return (one);
}
Fixed &Fixed::max(Fixed &one, Fixed &two) {
  if (one > two) return (one);
  return (two);
}
const Fixed &Fixed::max(const Fixed &one, const Fixed &two) {
  if ((Fixed)one > (Fixed)two) return (one);
  return (two);
}
