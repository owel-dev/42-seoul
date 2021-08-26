/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 15:30:59 by ulee              #+#    #+#             */
/*   Updated: 2021/08/26 15:31:00 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H
# include <sys/wait.h>
# include "libft/libft.h"

void	child_process(char **av, char **env, int *fd);
void	parent_process(char **av, char **env, int *fd);
void	error(void);
void	free_split(char **split);
char	*find_path(char *command, char **env);
void	run(char *av, char **env);

#endif
