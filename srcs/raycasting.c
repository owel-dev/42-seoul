/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 13:42:41 by ulee              #+#    #+#             */
/*   Updated: 2021/05/19 11:44:36 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_arr(t_info *io)
{
	init_player_dir(io);
	init_buffer(io);
	init_texture(io);
	load_texture(io);
	io->img.img = mlx_new_image(io->mlx, io->width, io->height);
	io->img.data = (int *)mlx_get_data_addr(\
		io->img.img, &io->img.bpp, &io->img.size_l, &io->img.endian);
}

void	init_ray(t_info *io, t_player *player, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)io->width - 1;
	ray->dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->dir_y = player->dir_y + player->plane_y * ray->camera_x;
	ray->map_x = (int)player->x;
	ray->map_y = (int)player->y;
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
	ray->hit = 0;
}

void	wall_cast(t_info *io)
{
	int	x;

	x = 0;
	cast_floor_ceiling(io);
	while (x < io->width)
	{
		init_ray(io, &io->player, &io->ray, x);
		set_step_first(&(io->ray), &(io->player));
		cast_ray(io, &(io->ray));
		get_perp_dist(&(io->ray), &(io->player));
		set_draw_height(io, &(io->ray));
		get_wall_texture(&(io->player), &(io->ray));
		get_wall_color(io, &(io->ray), x);
		io->z_buffer[x] = io->ray.perp_wall_dist;
		++x;
	}
}

void	sprite_cast(t_info *io)
{
	int	i;
	int	sprite;

	i = 0;
	sort_sprite(io, &(io->player));
	while (i < io->num_sprite)
	{
		translate_sprite(io, &(io->player), &(io->s_ray), i);
		calculate_sprite_height(io, &(io->s_ray));
		calculate_sprite_width(io, &(io->s_ray));
		sprite = io->s_ray.draw_start_x;
		while (sprite < io->s_ray.draw_end_x)
		{
			get_sprite_color(io, &(io->s_ray), sprite);
			++sprite;
		}
		++i;
	}
}
