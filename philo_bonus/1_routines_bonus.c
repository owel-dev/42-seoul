/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_routines_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 18:33:36 by ulee              #+#    #+#             */
/*   Updated: 2021/10/15 21:31:10 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	monitor_run(void *arg)
{
	t_philo *philo;
	int i;

	philo = (t_philo *)arg;
	while (1)
	{
		if (get_ms_time() - philo->when_last_eat >= philo->info->die_long)
		{
			// printf("%lld %lld\n", get_ms_time(), philo->when_last_eat);
			print_status(philo->info->philos[i], "died");
			exit(1);
		}
		if (philo->eat_count == philo->info->must_eat)
			exit(0);
		usleep(100);
	}
}

void	philo_run(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1)
	{
		// printf("%d\n",  philo->philo_num);
		eat(philo);
		sleepy(philo);
		think(philo);
		usleep(100);
	}
}

void	eat(t_philo *philo)
{
	// sem_wait(philo->info->fork);
	// printf("hello\n");
	philo->when_last_eat = get_ms_time();
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	// if (philo->info->infinite == 0)
		philo->eat_count++;
	while (get_ms_time() - philo->when_last_eat < philo->info->eat_long)
		usleep(600);
	// sem_post(philo->info->fork);
}

void	sleepy(t_philo *philo)
{
	long long time;

	time = get_ms_time();
	print_status(philo, "is sleeping");
	while (get_ms_time() - time < philo->info->sleep_long)
		usleep(500);
}

void	think(t_philo *philo)
{
	print_status(philo, "is thinking");
}
