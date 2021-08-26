/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 21:58:54 by ulee              #+#    #+#             */
/*   Updated: 2021/08/26 15:17:53 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	write_free(int *fd, char *add)
{
	write(fd[1], add, ft_strlen(add));
	free(add);
}

void	double_rd(char *limiter)
{
	int		pid;
	int		fd[2];
	char	*line;
	char	*add_newline;

	if (pipe(fd) == -1)
		error();
	pid = fork();
	if (pid == -1)
		error();
	if (pid == 0)
	{
		close(fd[0]);
		while (get_next_line(0, &line))
		{
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
				exit(0);
			add_newline = ft_strjoin(line, "\n");
			free(line);
			write_free(fd, add_newline);
		}
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	waitpid(pid, NULL, 0);
}

void	process(char *av, char **env)
{
	int	pid;
	int	fd[2];

	if (pipe(fd) == -1)
		error();
	pid = fork();
	if (pid == -1)
		error();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		run(av, env);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

int	main(int ac, char **av, char **env)
{
	int	file_out;
	int	file_in;
	int	i;

	if (ac < 5)
		error();
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		if (ac < 6)
			error();
		file_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
		double_rd(av[2]);
		i = 3;
	}
	else
	{
		file_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		file_in = open(av[1], O_RDONLY);
		dup2(file_in, STDIN_FILENO);
		i = 2;
	}
	while (i < ac - 2)
		process(av[i++], env);
	dup2(file_out, STDOUT_FILENO);
	run(av[ac - 2], env);
}
