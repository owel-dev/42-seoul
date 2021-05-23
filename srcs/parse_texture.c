/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 13:42:07 by ulee              #+#    #+#             */
/*   Updated: 2021/05/19 12:17:24 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_dup_texture(t_info *io, int flag)
{
	if (flag == N_TEX && io->north_file != NULL)
		print_error("check_texture");
	else if (flag == W_TEX && io->west_file != NULL)
		print_error("check_texture");
	else if (flag == E_TEX && io->east_file != NULL)
		print_error("check_texture");
	else if (flag == S_TEX && io->south_file != NULL)
		print_error("check_texture");
	else if (flag == SP_TEX && io->sprite_file != NULL)
		print_error("check_texture");
}

void	check_xpm(char *line)
{
	int	len;

	if (ft_strlen(line) <= ft_strlen(XPM_EXTENSION))
		print_error("check_xpm_len");
	len = ft_strlen(line) - ft_strlen(XPM_EXTENSION);
	if (ft_strncmp(line + len, XPM_EXTENSION, 4) != 0)
		print_error("check_xpm_ext");
}

void	check_space_path(char **path)
{
	int	i;

	i = 0;
	while (path[i] != NULL)
		++i;
	if (i == 3)
		print_error("check_space_path");
}
