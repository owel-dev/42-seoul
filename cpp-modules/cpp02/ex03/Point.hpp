/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 16:09:41 by ulee              #+#    #+#             */
/*   Updated: 2022/01/02 19:25:23 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_HPP
#define POINT_HPP

#include "Fixed.hpp"

class Point {
 private:
  const Fixed x;
  const Fixed y;

 public:
  Point();
  Point(const Fixed &obj);
  Point(const float _x, const float _y);
  Point &operator=(const Point &obj);
  ~Point();
  float getX(void) const;
  float getY(void) const;
};

#endif