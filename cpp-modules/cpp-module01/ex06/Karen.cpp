/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Karen.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 17:25:14 by ulee              #+#    #+#             */
/*   Updated: 2021/12/27 17:25:14 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Karen.hpp"

Karen::Karen() {}

void Karen::debug(void) { std::cerr << "Debug log...." << std::endl; }
void Karen::info(void) { std::cerr << "Info log...." << std::endl; }
void Karen::warning(void) { std::cerr << "Warning log...." << std::endl; }
void Karen::error(void) { std::cerr << "Error log...." << std::endl; }

std::string Karen::levels[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};

void Karen::complain(int level) {
  switch (level) {
    case DEBUG:
      debug();
      break;
    case INFO:
      info();
      break;
    case WARNING:
      warning();
      break;
    case ERROR:
      error();
      break;
    default:
      throw "Invalid log level";
      break;
  }
}

int Karen::filter(std::string av) {
  for (int i = 0; i < 4; i++) {
    if (av == levels[i]) {
      return i;
    }
  }
  return -1;
}
