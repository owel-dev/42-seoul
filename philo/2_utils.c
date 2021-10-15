/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 18:33:42 by ulee              #+#    #+#             */
/*   Updated: 2021/10/12 20:18:34 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_num(char *str)
{
	int i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int right_range(char *str)
{
	long long	num;
	int			is_minus;

	is_minus = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
		is_minus = 1;
	if (*str == '-' || *str == '+')
		str++;
	num = 0;
	while (ft_isdigit(*str))
	{
		num *= 10;
		num += *str - '0';
		if (num > 2147483648 && is_minus == 1)
			return (0);
		if (num > 2147483647 && is_minus == 0)
			return (0);
		str++;
	}
	return (1);
}

int	check_arg(int ac, char **av)
{
	int i;

	if (ac < 5 || ac > 6)
		return (-1);
	i = 1;
	while (i < ac)
	{
		if (av[i][0] == '-' || is_num(av[i]) == 0 || right_range(av[i]) == 0)
			return (-1);
		i++;
	}
	return (0);
}

long long	get_ms_time(void)
{
	struct timeval te;
	long long ms;

	gettimeofday(&te, NULL);
	ms = te.tv_sec * 1000 + te.tv_usec / 1000;
	return (ms);
}

void	print_status(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->info->print);
	if (philo->info->death == 1)
	{
		pthread_mutex_unlock(&philo->info->print);
		return ;
	}
	printf("%lld %d %s\n", get_ms_time() - philo->when_start, philo->philo_num, str);
	pthread_mutex_unlock(&philo->info->print);
}
