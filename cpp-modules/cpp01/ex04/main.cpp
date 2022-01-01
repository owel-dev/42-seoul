/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 13:52:40 by ulee              #+#    #+#             */
/*   Updated: 2021/12/27 19:54:59 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>

void replaceStr(std::string &str, std::string find, std::string replace) {
  std::string::size_type start;
  while ((start = str.find(find)) != std::string::npos) {
    str.erase(start, find.length());
    str.insert(start, replace);
  }
}

void replace(std::string file, std::string find, std::string replace) {
  if (!file.length() || !find.length() || !replace.length())
    throw "file is empty";

  std::ifstream open_file(file);
  if (!open_file.is_open()) throw "i-file is not open";

  std::ofstream write_file(file + ".replace", std::ios::trunc);
  if (!write_file.is_open()) throw "o-file is not open";

  std::string buffer;
  while (true) {
    std::getline(open_file, buffer);
    replaceStr(buffer, find, replace);
    write_file << buffer;
    if (open_file.eof()) break;
    write_file << '\n';
  }
}

int main(int ac, char **av) {
  if (ac != 4) {
    std::cerr << "Error: argument\n";
    return 1;
  }
  try {
    replace(av[1], av[2], av[3]);
  } catch (std::string e) {
    std::cerr << "Error: " << e << '\n';
    return 1;
  }
  return 0;
}