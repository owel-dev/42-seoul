/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 18:33:42 by ulee              #+#    #+#             */
/*   Updated: 2021/10/12 18:33:43 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
