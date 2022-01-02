/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 16:09:45 by ulee              #+#    #+#             */
/*   Updated: 2022/01/02 19:18:30 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

Point::Point() : x(0), y(0) {}
Point::Point(const Fixed &obj) { *this = obj; }
Point::Point(const float _x, const float _y) : x(_x), y(_y) {}
Point &Point::operator=(const Point &obj) {
  (Fixed) this->x = obj.x;
  (Fixed) this->x = obj.y;
  return (*this);
}
Point::~Point() {}
float Point::getX(void) const { return (this->x.toFloat()); }
float Point::getY(void) const { return (this->y.toFloat()); }