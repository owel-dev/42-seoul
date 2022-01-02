/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 19:25:17 by ulee              #+#    #+#             */
/*   Updated: 2022/01/02 19:49:41 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

float area(Point const p1, Point const p2, Point const point) {
  return (std::abs((p1.getX() * (p2.getY() - point.getY()) +
                    p2.getX() * (point.getY() - p1.getY()) +
                    point.getX() * (p1.getY() - p2.getY())) /
                   2.0));
}

bool bsp(Point const a, Point const b, Point const c, Point const point) {
  float triangle = area(a, b, c);
  float sub_triangle1 = area(a, b, point);
  float sub_triangle2 = area(a, c, point);
  float sub_triangle3 = area(b, c, point);

  std::cout << triangle << " " << sub_triangle1 << " " << sub_triangle2 << " "
            << sub_triangle3 << std::endl;
  return (std::abs(sub_triangle1 + sub_triangle2 + sub_triangle3 - triangle) <
          __DBL_EPSILON__);
}