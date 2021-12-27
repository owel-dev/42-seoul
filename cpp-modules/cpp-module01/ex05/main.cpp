/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 13:52:33 by ulee              #+#    #+#             */
/*   Updated: 2021/12/27 17:29:44 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Karen.hpp"

int main() {
  Karen karen;
  karen.complain("debug");
  karen.complain("info");
  karen.complain("warning");
  karen.complain("error");

  return 0;
}