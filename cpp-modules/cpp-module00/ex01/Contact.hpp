/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 20:08:04 by ulee              #+#    #+#             */
/*   Updated: 2021/12/25 00:38:31 by ulee             ###   ########.fr       */
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