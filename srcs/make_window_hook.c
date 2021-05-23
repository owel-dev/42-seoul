/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_window_hook.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 13:41:39 by ulee              #+#    #+#             */
/*   Updated: 2021/05/19 11:43:23 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_info *io, t_player *player, double move_speed)
{
	if (io->map[(int)player->y]\
					[(int)(player->x + player->dir_x * move_speed)] != '1')
		player->x += player->dir_x * move_speed;
	if (io->map[(int)(player->y + player->dir_y * move_speed)]\
					[(int)player->x] != '1')
		player->y += player->dir_y * move_speed;
}

void	move_player_left_right(t_info *io, \
								t_player *player, double move_speed)
{
	if (io->map[(int)player->y]\
					[(int)(player->x + player->dir_y * move_speed)] != '1')
		player->x += player->dir_y * move_speed;
	if (io->map[(int)(player->y + -player->dir_x * move_speed)]\
					[(int)player->x] != '1')
		player->y += -player->dir_x * move_speed;
}

void	key_update(t_info *io)
{
	if (io->key.w)
		move_player(io, &io->player, io->player.move_speed);
	if (io->key.s)
		move_player(io, &io->player, -io->player.move_speed);
	if (io->key.a)
		move_player_left_right(io, &io->player, io->player.move_speed);
	if (io->key.d)
		move_player_left_right(io, &io->player, -io->player.move_speed);
	if (io->key.left)
		rotate_player(&io->player, -io->player.rot_speed);
	if (io->key.right)
		rotate_player(&io->player, io->player.rot_speed);
}

int		key_press(int key, t_info *io)
{
	if (key == KEY_W || key == KEY_AR_U)
		io->key.w = 1;
	else if (key == KEY_S || key == KEY_AR_D)
		io->key.s = 1;
	else if (key == KEY_A)
		io->key.a = 1;
	else if (key == KEY_D)
		io->key.d = 1;
	else if (key == KEY_AR_L)
		io->key.left = 1;
	else if (key == KEY_AR_R)
		io->key.right = 1;
	else if (key == KEY_ESC)
		exit(0);
	return (0);
}

int		key_release(int key, t_info *io)
{
	if (key == KEY_W || key == KEY_AR_U)
		io->key.w = 0;
	else if (key == KEY_S || key == KEY_AR_D)
		io->key.s = 0;
	else if (key == KEY_A)
		io->key.a = 0;
	else if (key == KEY_D)
		io->key.d = 0;
	else if (key == KEY_AR_L)
		io->key.left = 0;
	else if (key == KEY_AR_R)
		io->key.right = 0;
	else if (key == KEY_ESC)
		exit(0);
	return (0);
}
