/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 21:59:02 by ulee              #+#    #+#             */
/*   Updated: 2021/08/26 15:15:08 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(char **av, char **env, int *fd)
{
	int	file_in;

	file_in = open(av[1], O_RDONLY, 0777);
	if (file_in == -1)
		error();
	dup2(fd[1], STDOUT_FILENO);
	dup2(file_in, STDIN_FILENO);
	close(fd[0]);
	run(av[2], env);
}

void	parent_process(char **av, char **env, int *fd)
{
	int	file_out;

	file_out = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file_out == -1)
		error();
	dup2(fd[0], STDIN_FILENO);
	dup2(file_out, STDOUT_FILENO);
	close(fd[1]);
	run(av[3], env);
}

int	main(int ac, char **av, char **env)
{
	int	pid;
	int	fd[2];

	if (ac != 5)
		error();
	if (pipe(fd) == -1)
		error();
	pid = fork();
	if (pid == -1)
		error();
	if (pid == 0)
		child_process(av, env, fd);
	waitpid(pid, NULL, 0);
	parent_process(av, env, fd);
	close(fd[0]);
	close(fd[1]);
	return (0);
}
