/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 13:41:07 by ulee              #+#    #+#             */
/*   Updated: 2021/05/19 11:39:23 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_argu(char *argu)
{
	char	*ext;

	if (ft_strlen(argu) <= 4)
		return (1);
	ext = ft_strrchr(argu, '.');
	if (ext == NULL)
		return (1);
	if (ft_strncmp(ext, ".cub", 4) != 0)
		return (1);
	return (0);
}

void	free_cub(t_info *io)
{
	if (io->img.img)
		mlx_destroy_image(io->mlx, io->img.img);
	if (io->sprite)
		ft_free(io->sprite);
	if (io->buf)
		arr_free((void *)io->buf);
	if (io->z_buffer)
		ft_free(io->z_buffer);
	if (io->texture)
		ft_free(io->texture);
	if (io->map)
		arr_free(io->map);
	if (io->mlx && io->win)
		mlx_destroy_window(io->mlx, io->win);
	exit(0);
}
