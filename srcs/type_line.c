/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 13:43:07 by ulee              #+#    #+#             */
/*   Updated: 2021/05/17 14:25:50 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_tex(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (N_TEX);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (S_TEX);
	else if (ft_strncmp(line, "S ", 2) == 0)
		return (SP_TEX);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (W_TEX);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (E_TEX);
	return (0);
}

int	is_map(char *line)
{
	while (*line)
	{
		if (ft_strchr(MAP_CHAR, *line) == NULL)
			return (0);
		line++;
	}
	return (1);
}
