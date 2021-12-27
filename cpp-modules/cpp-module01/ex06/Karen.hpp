/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Karen.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 17:25:16 by ulee              #+#    #+#             */
/*   Updated: 2021/12/27 17:25:16 by ulee             ###   ########.fr       */
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
  void complain(int level);
  int filter(std::string av);
};

enum ENUM_LEVELS { DEBUG = 0, INFO, WARNING, ERROR };
