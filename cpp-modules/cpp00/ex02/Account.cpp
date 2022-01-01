/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Account.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 00:33:27 by a_ulee            #+#    #+#             */
/*   Updated: 2021/12/25 00:38:42 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Account.hpp"

#include <time.h>

#include <iomanip>
#include <iostream>

int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

Account::Account(void) {
  this->_accountIndex = _nbAccounts++;
  this->_amount = 0;
  this->_nbDeposits = 0;
  this->_nbWithdrawals = 0;
  _displayTimestamp();
  std::cout << "index:" << this->_accountIndex << ';'
            << "amount:" << this->_amount << ';' << "created" << '\n';
}

Account::Account(int balance) {
  this->_accountIndex = Account::_nbAccounts++;
  this->_amount = balance;
  Account::_totalAmount += this->_amount;
  this->_nbDeposits = 0;
  this->_nbWithdrawals = 0;
  _displayTimestamp();
  std::cout << "index:" << this->_accountIndex << ';'
            << "amount:" << this->_amount << ';' << "created" << '\n';
}

Account::~Account(void) {
  _displayTimestamp();
  std::cout << "index:" << this->_accountIndex << ';'
            << "amount:" << this->_amount << ';' << "closed" << '\n';
}

int Account::getNbAccounts(void) { return Account::_nbAccounts; }
int Account::getTotalAmount(void) { return Account::_totalAmount; }
int Account::getNbDeposits(void) { return Account::_totalNbDeposits; }
int Account::getNbWithdrawals(void) { return Account::_totalNbWithdrawals; }

void Account::_displayTimestamp(void) {
  std::chrono::time_point<std::chrono::system_clock> now =
      std::chrono::system_clock::now();
  std::time_t time_now = std::chrono::system_clock::to_time_t(now);
  tm *local_t = localtime(&time_now);

  int year = local_t->tm_year + 1900;
  int month = local_t->tm_mon + 1;
  int day = local_t->tm_mday;
  int hour = local_t->tm_hour;
  int min = local_t->tm_min;
  int sec = local_t->tm_sec;

  std::cout << std::setfill('0') << "[" << year << std::setw(2) << month
            << std::setw(2) << day << "_" << std::setw(2) << hour
            << std::setw(2) << min << std::setw(2) << sec << "]"
            << " ";
}

void Account::displayAccountsInfos(void) {
  _displayTimestamp();
  std::cout << "accounts:" << Account::_nbAccounts << ';'
            << "total:" << Account::_totalAmount << ';'
            << "deposits:" << Account::_totalNbDeposits << ';'
            << "widthrawals:" << Account::_totalNbWithdrawals << '\n';
}

void Account::displayStatus(void) const {
  _displayTimestamp();
  std::cout << "index:" << this->_accountIndex << ';'
            << "amount:" << this->_amount << ';'
            << "deposit:" << this->_nbDeposits << ';'
            << "withrawals:" << this->_nbWithdrawals << '\n';
}

void Account::makeDeposit(int deposit) {
  if (deposit != 0) {
    this->_nbDeposits++;
    Account::_totalNbDeposits++;
  }
  int p_amount = this->_amount;
  this->_amount += deposit;

  Account::_totalAmount += deposit;

  _displayTimestamp();
  std::cout << "index:" << this->_accountIndex << ';' << "p_amount:" << p_amount
            << ';' << "deposit:" << deposit << ';' << "amount:" << this->_amount
            << ';' << "nb_deposits:" << this->_nbDeposits << '\n';
}

bool Account::makeWithdrawal(int withdrawal) {
  _displayTimestamp();
  std::cout << "index:" << this->_accountIndex << ';'
            << "p_amount:" << this->_amount << ';';

  if (this->_amount >= withdrawal) {
    this->_nbWithdrawals++;
    Account::_totalNbWithdrawals++;

    this->_amount -= withdrawal;
    Account::_totalAmount -= withdrawal;

    std::cout << "withdrawal:" << withdrawal << ';'
              << "amount:" << this->_amount << ';'
              << "nb_withdrawal:" << this->_nbWithdrawals << '\n';
    return (true);
  } else {
    std::cout << "withdrawal:refused" << ';' << '\n';
  }
  return (false);
}

int Account::checkAmount(void) const { return (this->_amount); }
