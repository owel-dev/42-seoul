/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 21:59:00 by ulee              #+#    #+#             */
/*   Updated: 2021/08/26 15:29:55 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(void)
{
	ft_printf("error!\n");
	exit(1);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (split == NULL)
		error();
	while (split[i])
		free(split[i++]);
	free(split);
}

char	*find_path(char *command, char **env)
{
	char	**path_split;
	char	*slash_path;
	char	*path;
	int		i;

	i = 0;
	while (ft_strnstr(env[i], "PATH", 4) == 0)
		i++;
	path_split = ft_split(env[i] + 5, ':');
	i = 0;
	while (path_split[i])
	{
		slash_path = ft_strjoin(path_split[i], "/");
		path = ft_strjoin(slash_path, command);
		free(slash_path);
		if (access(path, F_OK) == 0)
		{
			free_split(path_split);
			return (path);
		}
		free(path);
		i++;
	}
	free_split(path_split);
	return (0);
}

void	run(char *av, char **env)
{
	char	*command;
	char	**av_split;

	av_split = ft_split(av, ' ');
	command = find_path(av_split[0], env);
	if (command == NULL || av_split == NULL)
		error();
	if (execve(command, av_split, env) == -1)
		error();
}
