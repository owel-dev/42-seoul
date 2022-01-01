/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Karen.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 17:25:03 by ulee              #+#    #+#             */
/*   Updated: 2021/12/27 17:25:03 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <iostream>

class Karen {
 private:
  void debug(void);
  void info(void);
  void warning(void);
  void error(void);
  static std::string levels[4];

 public:
  Karen();
  void complain(std::string level);
};
