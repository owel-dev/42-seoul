/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Karen.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 17:24:59 by ulee              #+#    #+#             */
/*   Updated: 2021/12/27 17:29:47 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Karen.hpp"

Karen::Karen() {}

void Karen::debug(void) { std::cerr << "Debug log...." << std::endl; }
void Karen::info(void) { std::cerr << "Info log...." << std::endl; }
void Karen::warning(void) { std::cerr << "Warning log...." << std::endl; }
void Karen::error(void) { std::cerr << "Error log...." << std::endl; }

std::string Karen::levels[4] = {"debug", "info", "warning", "error"};

void Karen::complain(std::string level) {
  void (Karen::*pFunction[4])(void) = {&Karen::debug, &Karen::info,
                                       &Karen::warning, &Karen::error};
  for (int i = 0; i < 4; i++) {
    if (level == levels[i]) {
      (this->*pFunction[i])();
      return;
    }
  }
}