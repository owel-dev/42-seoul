/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_resolution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 13:42:03 by ulee              #+#    #+#             */
/*   Updated: 2021/05/17 14:21:17 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_screen(t_info *io, char **size)
{
	mlx_get_screen_size(io->mlx, &io->max_width, &io->max_height);
	if (ft_atoi(size[1]) > io->max_width)
		io->width = io->max_width;
	else
		io->width = ft_atoi(size[1]);
	if (ft_atoi(size[2]) > io->max_height)
		io->height = io->max_height;
	else
		io->height = ft_atoi(size[2]);
}
