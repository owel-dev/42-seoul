/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_philo_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 18:33:12 by ulee              #+#    #+#             */
/*   Updated: 2021/10/14 17:58:44 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	set_info(t_info *info, int ac, char **av)
{
	info->philo_count = ft_atoi(av[1]);
	info->die_long = ft_atoi(av[2]);
	info->eat_long = ft_atoi(av[3]);
	info->sleep_long = ft_atoi(av[4]);
	info->must_eat = -1;
	info->infinite = 1;
	if (ac == 6)
	{
		info->infinite = 0;
		info->must_eat = ft_atoi(av[5]);
	}
	info->death = 0;
	return (0);
}

int	set_fork(t_info *info)
{
	int i;

	i = 0;
	info->fork = sem_open("fork", O_CREAT, 0644, info->philo_count);
	if (info->fork == SEM_FAILED)
		return (-1);
	return (0);
}

int	set_philos(t_info *info)
{
	int i;
	long long time;

	info->philos = (t_philo **)malloc(sizeof(t_philo *) * info->philo_count);
	if (info->philos == NULL)
		return (-1);
	i = 0;
	time = get_ms_time();
	while (i < info->philo_count)
	{
		info->philos[i] = (t_philo *)malloc(sizeof(t_philo));
		if (info->philos[i] == NULL)
			return (-1);
		info->philos[i]->when_last_eat = time;
		info->philos[i]->when_start = time;
		info->philos[i]->philo_num = i + 1;
		info->philos[i]->info = info;
		info->philos[i]->left_fork = i;
		info->philos[i]->right_fork = (i + 1) % info->philo_count;
		info->philos[i]->eat_count = 0;
		i++;
	}
	return (0);
}

void kill_all_process(t_info *info)
{
	int i;

	i = 0;
	while (i < info->philo_count)
		kill(info->philos[i++]->pid, SIGKILL);
}

void receive_signal(t_info *info)
{
	int i;
	int status;
	int eat_count;

	i = 0;
	eat_count = 0;
	while(i < info->philo_count)
	{
		waitpid(-1, &status, 0);
		if (status == 256)
		{
			kill_all_process(info);
			return ;
		}
		if (status == 0)
			eat_count++;
		if (eat_count == info->must_eat)
			return ;
		i++;
	}
}

int	make_process(t_info *info)
{
	int i;

	i = 0;
	while (i < info->philo_count)
	{
		info->philos[i]->pid = fork();
		if (info->philos[i]->pid == 0)
		{
			if (pthread_create(&info->moniter_id, NULL, \
				(void *)&monitor_run, (void *)info->philos[i]) != 0)
				return (-1);
			// printf("%d\n",  info->philos[i]->philo_num);
			philo_run(info->philos[i]);
		}
		i++;
		usleep(100);
	}
	receive_signal(info);
	return (0);
}

int	main(int ac, char **av) {
	t_info info;

	if (check_arg(ac, av) == -1)
		return (-1);
	if (set_info(&info ,ac, av) == -1)
		return (-1);
	if (set_fork(&info) == -1)
		return (-1);
	if (set_philos(&info) == -1)
		return (-1);
	if (make_process(&info) == -1)
		return (-1);
	return (0);
}
