/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_cast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 13:42:54 by ulee              #+#    #+#             */
/*   Updated: 2021/05/19 11:45:52 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sort_sprite(t_info *io, t_player *player)
{
	int	i;

	i = 0;
	while (i < io->num_sprite)
	{
		io->sprite[i].distance = ((player->x - io->sprite[i].x) * (player->x - \
		io->sprite[i].x) + (player->y - io->sprite[i].y) * (player->y - \
		io->sprite[i].y));
		i++;
	}
	sort(io);
}

void	translate_sprite(\
				t_info *io, t_player *player, t_sprite_ray *s_ray, int i)
{
	double	v_mode;

	v_mode = 0.0;
	s_ray->x = io->sprite[i].x - player->x;
	s_ray->y = io->sprite[i].y - player->y;
	s_ray->inversion_detection = 1.0 / (player->plane_x * player->dir_y - \
	player->dir_x * player->plane_y);
	s_ray->transform_x = s_ray->inversion_detection * (player->dir_y * \
	s_ray->x - player->dir_x * s_ray->y);
	s_ray->transform_y = s_ray->inversion_detection * (-player->plane_y * \
		s_ray->x + player->plane_x * s_ray->y);
	s_ray->screen_x = (int)((io->width / 2) * (1 + s_ray->transform_x / \
	s_ray->transform_y));
	s_ray->v_move_screen = (int)(v_mode / s_ray->transform_y);
}

void	calculate_sprite_height(t_info *io, t_sprite_ray *s_ray)
{
	int	v_div;

	v_div = 1;
	s_ray->height = (int)fabs((io->height / s_ray->transform_y) / v_div);
	s_ray->draw_start_y = -s_ray->height / 2 + io->height / 2 + \
	s_ray->v_move_screen;
	if (s_ray->draw_start_y < 0)
		s_ray->draw_start_y = 0;
	s_ray->draw_end_y = s_ray->height / 2 + io->height / 2 + \
	s_ray->v_move_screen;
	if (s_ray->draw_end_y >= io->height)
		s_ray->draw_end_y = io->height - 1;
}

void	calculate_sprite_width(t_info *io, t_sprite_ray *s_ray)
{
	int	u_div;

	u_div = 1;
	s_ray->width = (int)fabs((io->height / s_ray->transform_y) / u_div);
	s_ray->draw_start_x = -s_ray->width / 2 + s_ray->screen_x;
	if (s_ray->draw_start_x < 0)
		s_ray->draw_start_x = 0;
	s_ray->draw_end_x = s_ray->width / 2 + s_ray->screen_x;
	if (s_ray->draw_end_x >= io->width)
		s_ray->draw_end_x = io->width - 1;
}

void	get_sprite_color(t_info *io, t_sprite_ray *s_ray, int stripe)
{
	int	color;
	int	y;
	int	draw;

	s_ray->tex_x =\
		(int)((256 * (stripe - (-s_ray->width / 2 + s_ray->screen_x)) * \
			TEX_WIDTH / s_ray->width) / 256);
	if (s_ray->transform_y > 0 && stripe > 0 &&\
		stripe < io->width && s_ray->transform_y < io->z_buffer[stripe])
	{
		y = s_ray->draw_start_y;
		while (y < s_ray->draw_end_y)
		{
			draw = (y - s_ray->v_move_screen) * 256 -\
					io->height * 128 + s_ray->height * 128;
			s_ray->tex_y = ((draw * TEX_HEIGHT) / s_ray->height) / 256;
			color = io->texture[4][TEX_WIDTH * s_ray->tex_y + s_ray->tex_x];
			if ((color & 0x00FFFFFF) != 0)
				io->buf[y][stripe] = color;
			y++;
		}
	}
}
