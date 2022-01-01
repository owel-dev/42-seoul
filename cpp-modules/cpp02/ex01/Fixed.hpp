/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 16:35:18 by ulee              #+#    #+#             */
/*   Updated: 2022/01/01 16:35:18 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
  Fixed &operator=(Fixed const &obj);
  void setRawBits(int const raw);
  float toFloat(void) const;
  int toInt(void) const;
};

std::ostream &operator<<(std::ostream &out, Fixed const &obj);
