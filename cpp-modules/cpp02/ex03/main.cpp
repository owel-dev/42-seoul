/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 16:35:37 by ulee              #+#    #+#             */
/*   Updated: 2022/01/02 19:52:17 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include "Point.hpp"

bool bsp(Point const a, Point const b, Point const c, Point const point);

int main() {
  Point a(0, 0);
  Point b(10, 10.5);
  Point c(10, 0);
  Point inner_point(5, 3);
  Point outter_point(5, 20);

  std::cout << "Inner point: " << bsp(a, b, c, inner_point) << std::endl;
  std::cout << std::endl;
  std::cout << "Outter point: " << bsp(a, b, c, outter_point) << std::endl;
  return 0;
}