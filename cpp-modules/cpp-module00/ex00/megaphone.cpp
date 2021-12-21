/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 20:05:16 by ulee              #+#    #+#             */
/*   Updated: 2021/12/21 20:05:17 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  <iostream>

int main(int argc, char *argv[])
{
	std::string str;

	if (argc == 1)
	{
		std::cout <<  "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
		return 0;
	}
	for (int i = 1; i < argc; i++)
	{
		str = argv[i];

		for (size_t i = 0; i < str.length(); i++)
			if (97 <= str[i] && str[i] <= 122)
				str[i] -= 32;

		if (i == argc - 1)
			std::cout << str << std::endl;
		else
			std::cout << str;
	}
	return 0;
}
