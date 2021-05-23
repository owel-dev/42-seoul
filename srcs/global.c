/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 13:40:42 by ulee              #+#    #+#             */
/*   Updated: 2021/05/19 11:38:58 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_exit(int ret)
{
	exit(ret);
	return (ret);
}

void	print_error(char *log)
{
	ft_printf("%s ERROR\n", log);
	exit(1);
}

void	arr_free(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		arr[i] = NULL;
		++i;
	}
	free(arr);
	arr = NULL;
}

void	list_free(t_info *io)
{
	int	i;

	i = 0;
	while (io->li != NULL)
	{
		free(io->li);
		io->li = io->li->next;
	}
}

void	del_list(void *content)
{
	if (content != NULL)
		free(content);
	content = NULL;
}
