/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Phonebook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 00:33:22 by a_ulee            #+#    #+#             */
/*   Updated: 2021/12/25 00:38:39 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include <iomanip>
#include <iostream>
#include <string>

#include "Contact.hpp"

class Phonebook {
 private:
  Contact contact[8];
  int amount;
  int add_count;

 public:
  Phonebook();
  ~Phonebook();
  void add(void);
  void search(void);
  void secret(void);
  void printHeader(void);
  void printAllFileds(void);
};

#endif