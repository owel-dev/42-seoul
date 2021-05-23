/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 13:41:18 by ulee              #+#    #+#             */
/*   Updated: 2021/05/17 17:39:23 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_player *player)
{
	player->x = 2;
	player->y = 5;
	player->dir_x = -1.0;
	player->dir_y = 0.0;
	player->plane_x = 0.0;
	player->plane_y = 0.66;
	player->move_speed = 0.06;
	player->rot_speed = 0.02;
}

void	init_player_dir(t_info *io)
{
	int	rot;
	int	direction;

	rot = 0;
	direction = io->dir;
	if (direction == 'S')
		rot = 270;
	else if (direction == 'N')
		rot = 90;
	else if (direction == 'E')
		rot = 180;
	else if (direction == 'W')
		rot = 0;
	rotate_player(&io->player, rot * (PI / 180));
}

void	init_buffer(t_info *io)
{
	int	i;

	i = 0;
	io->buf = ft_calloc(io->height, sizeof(int **));
	if (io->buf == NULL)
		return (print_error("init_buffer"));
	while (i < io->height)
	{
		io->buf[i] = ft_calloc(io->width, sizeof(int *));
		if (io->buf[i] == NULL)
			return (print_error("init_buffer"));
		i++;
	}
	io->z_buffer = ft_calloc(io->width, sizeof(double *));
	if (io->z_buffer == NULL)
		return (print_error("init_buffer"));
}

void	init_texture(t_info *io)
{
	int	i;
	int	j;

	io->texture = (int **)malloc(sizeof(int *) * 5);
	if (io->texture == NULL)
		return (print_error("init_buffer"));
	i = 0;
	while (i < 5)
	{
		io->texture[i] =\
				(int *)malloc(sizeof(int) * (TEX_HEIGHT * TEX_WIDTH));
		if (io->texture == NULL)
			return (print_error("init_buffer"));
		j = 0;
		while (j < TEX_HEIGHT * TEX_WIDTH)
		{
			io->texture[i][j] = 0;
			j++;
		}
		i++;
	}
}

void	load_texture(t_info *io)
{
	t_img	img;

	check_texture_file_exists(io);
	load_image(io, io->texture[3], io->north_file, &img);
	load_image(io, io->texture[2], io->south_file, &img);
	load_image(io, io->texture[1], io->west_file, &img);
	load_image(io, io->texture[0], io->east_file, &img);
	load_image(io, io->texture[4], io->sprite_file, &img);
	ft_free(io->north_file);
	ft_free(io->south_file);
	ft_free(io->west_file);
	ft_free(io->east_file);
	ft_free(io->sprite_file);
}
