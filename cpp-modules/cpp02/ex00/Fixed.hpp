/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 16:35:07 by ulee              #+#    #+#             */
/*   Updated: 2022/01/01 16:35:08 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

class Fixed {
 private:
  int value;
  static const int bits = 8;

 public:
  Fixed();
  Fixed(const Fixed &obj);
  ~Fixed();
  int getRawBits(void) const;
  Fixed &operator=(Fixed const &obj);
  void setRawBits(int const raw);
};
