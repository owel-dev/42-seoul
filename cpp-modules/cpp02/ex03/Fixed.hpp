/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 16:35:34 by ulee              #+#    #+#             */
/*   Updated: 2022/01/02 19:49:37 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

#include <cmath>
#include <iostream>

class Fixed {
 private:
  int value;
  static const int bits = 8;

 public:
  Fixed();
  Fixed(const Fixed &obj);
  Fixed(const int num);
  Fixed(const float num);
  ~Fixed();
  int getRawBits(void) const;
  Fixed &operator=(const Fixed &obj);
  void setRawBits(const int raw);
  float toFloat(void) const;
  int toInt(void) const;

  bool operator>(const Fixed &obj);
  bool operator<(const Fixed &obj);
  bool operator>=(const Fixed &obj);
  bool operator<=(const Fixed &obj);
  bool operator==(const Fixed &obj);
  bool operator!=(const Fixed &obj);

  Fixed operator+(const Fixed &obj);
  Fixed operator-(const Fixed &obj);
  Fixed operator*(const Fixed &obj);
  Fixed operator/(const Fixed &obj);

  Fixed operator++(int);
  Fixed &operator++();
  Fixed operator--(int);
  Fixed &operator--();

  static Fixed &min(Fixed &one, Fixed &two);
  static const Fixed &min(const Fixed &one, const Fixed &two);
  static Fixed &max(Fixed &one, Fixed &two);
  static const Fixed &max(const Fixed &one, const Fixed &two);
};

std::ostream &operator<<(std::ostream &out, Fixed const &obj);

#endif