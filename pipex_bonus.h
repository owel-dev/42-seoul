/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 21:58:57 by ulee              #+#    #+#             */
/*   Updated: 2021/08/26 15:27:13 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H

# define PIPEX_BONUS_H
# include <sys/wait.h>
# include "libft/libft.h"

void	write_free(int *fd, char *add);
void	double_rd(char *limiter);
void	process(char *av, char **env);
void	error(void);
void	free_split(char **split);
char	*find_path(char *command, char **env);
void	run(char *av, char **env);

#endif
