/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player_dir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 13:41:11 by ulee              #+#    #+#             */
/*   Updated: 2021/05/17 17:26:53 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_player(t_player *player, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(rot_speed) - \
					player->dir_y * sin(rot_speed);
	player->dir_y = old_dir_x * sin(rot_speed) + \
					player->dir_y * cos(rot_speed);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(rot_speed) - \
					player->plane_y * sin(rot_speed);
	player->plane_y = old_plane_x * sin(rot_speed) + \
					player->plane_y * cos(rot_speed);
}

void	init_key(t_info *io)
{
	io->key.w = 0;
	io->key.s = 0;
	io->key.d = 0;
	io->key.a = 0;
	io->key.left = 0;
	io->key.right = 0;
}
