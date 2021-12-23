/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a_ulee <a_ulee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 20:08:04 by ulee              #+#    #+#             */
/*   Updated: 2021/12/23 15:49:27 by a_ulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <iomanip>
#include <iostream>
#include <string>

class Contact {
 private:
  std::string darkest_secret;
  std::string password;
  std::string field_list[6];
  static std::string field_name[6];
  enum Field { FirstName = 0, LastName, NickName, PhoneNumber, DarkestSecret };

 public:
  Contact();
  ~Contact();
  void printHeader(void);
  void setFields(void);
  void printField(void);
  void printSecret(void);
};

#endif