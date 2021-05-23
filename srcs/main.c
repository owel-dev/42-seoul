/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 13:40:31 by ulee              #+#    #+#             */
/*   Updated: 2021/05/19 11:42:39 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parsing(t_info *io)
{
	init_player(&(io->player));
	init_key(io);
	io->mlx = mlx_init();
	init_parse_info(io);
	parse_file(io);
}

void	ray_casting(t_info *io)
{
	wall_cast(io);
	sprite_cast(io);
	draw_image(io);
}

int		main_loop(t_info *io)
{
	ray_casting(io);
	mlx_put_image_to_window(io->mlx, io->win, io->img.img, 0, 0);
	key_update(io);
	return (0);
}

void	make_window_hook(t_info *io)
{
	io->win = \
			mlx_new_window(io->mlx, io->width, io->height, "someTitle");
	mlx_hook(io->win, X_EVENT_KEY_PRESS, 0, key_press, io);
	mlx_hook(io->win, X_EVENT_KEY_RELEASE, 0, key_release, io);
	mlx_hook(io->win, X_EVENT_KEY_EXIT, 0, ft_exit, 0);
	mlx_loop_hook(io->mlx, main_loop, io);
	mlx_loop(io->mlx);
}

int		main(int ac, char **av)
{
	t_info	io;
	int		is_save;

	is_save = 0;
	if (ac == 3)
		is_save = 1;
	if (ac != is_save + 2 || check_argu(av[1]))
		print_error("main_argument");
	io.fd = open(av[1], O_RDONLY);
	if (io.fd == -1)
		print_error("main_open");
	parsing(&io);
	init_arr(&io);
	if (is_save == 1)
	{
		if (ft_strlen(av[2]) != 6 || ft_strncmp(av[2], "--save", 6) != 0)
			print_error("main_save");
		ray_casting(&io);
		save_bmp(&io);
		return (0);
	}
	make_window_hook(&io);
	free_cub(&io);
	return (0);
}
