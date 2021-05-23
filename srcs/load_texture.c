/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 13:41:22 by ulee              #+#    #+#             */
/*   Updated: 2021/05/17 14:14:27 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_texture_file_exists(t_info *io)
{
	int		fd;
	int		check[5];

	fd = 0;
	ft_bzero(check, 20);
	fd = open(io->west_file, O_RDONLY);
	check[0] = fd;
	fd = open(io->east_file, O_RDONLY);
	check[1] = fd;
	fd = open(io->south_file, O_RDONLY);
	check[2] = fd;
	fd = open(io->north_file, O_RDONLY);
	check[3] = fd;
	fd = open(io->sprite_file, O_RDONLY);
	check[4] = fd;
	close(fd);
	if (ft_memchr(check, -1, 20) != NULL)
		print_error("check_texture_file_exists");
}

void	load_image(t_info *io, int *texture, char *path, t_img *img)
{
	int		x;
	int		y;

	img->img = mlx_xpm_file_to_image(\
					io->mlx, path, &img->width, &img->height);
	img->data = (int *)mlx_get_data_addr(\
					img->img, &img->bpp, &img->size_l, &img->endian);
	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			texture[img->width * y + x] =\
					img->data[img->width * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(io->mlx, img->img);
}

void	ft_free(void *s)
{
	free(s);
	s = NULL;
}
