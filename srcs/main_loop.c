/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 13:41:27 by ulee              #+#    #+#             */
/*   Updated: 2021/05/17 14:15:51 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_image(t_info *io)
{
	int	x;
	int	y;
	int	k;

	y = 0;
	while (y < io->height)
	{
		x = 0;
		k = io->width - 1;
		while (x < io->width)
		{
			io->img.data[io->width * y + k] = io->buf[y][x];
			x++;
			k--;
		}
		y++;
	}
}
