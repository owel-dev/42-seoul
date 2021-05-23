/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_cast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 13:43:10 by ulee              #+#    #+#             */
/*   Updated: 2021/05/19 11:45:34 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cast_floor_ceiling(t_info *io)
{
	int	y;
	int	x;

	y = 0;
	while (y < io->height)
	{
		x = 0;
		while (x < io->width)
		{
			if (y > io->height / 2)
				io->buf[y][x] = io->floor_color;
			else
				io->buf[y][x] = io->ceiling_color;
			++x;
		}
		++y;
	}
}

void	set_step_first(t_ray *ray, t_player *player)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->y) * ray->delta_dist_y;
	}
}

void	cast_ray(t_info *io, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			if (ray->step_x == -1)
				ray->side = 0;
			else
				ray->side = 1;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			if (ray->step_y == -1)
				ray->side = 2;
			else
				ray->side = 3;
		}
		if (io->map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

void	get_perp_dist(t_ray *ray, t_player *player)
{
	if (ray->side <= 1)
		ray->perp_wall_dist =\
			(ray->map_x - player->x + (1 - ray->step_x) / 2) / ray->dir_x;
	else
		ray->perp_wall_dist =\
			(ray->map_y - player->y + (1 - ray->step_y) / 2) / ray->dir_y;
}

void	set_draw_height(t_info *io, t_ray *ray)
{
	ray->line_height = (int)(io->height / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + io->height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + io->height / 2;
	if (ray->draw_end >= io->height)
		ray->draw_end = io->height - 1;
}
