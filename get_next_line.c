/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 21:04:31 by ulee              #+#    #+#             */
/*   Updated: 2021/01/20 21:22:08 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		isnewline(char **backup, char **line)
{
	char	*newline;
	char	*temp;

	if (!(newline = ft_strchr(*backup, '\n')))
		return (0);
	*newline = '\0';
	if (!(*line = ft_strdup(*backup)))
		return (-1);
	if (!(temp = ft_strdup(++newline)))
		return (-1);
	free(*backup);
	*backup = temp;
	return (1);
}

int		backup_clean(char **backup, char **line, int read_size)
{
	if (read_size < 0)
		return (-1);
	if (*backup && (isnewline(backup, line)))
		return (1);
	else if (*backup)
	{
		if (!(*line = ft_strdup(*backup)))
			return (-1);
		free(*backup);
		*backup = NULL;
		return (0);
	}
	if (!(*line = ft_strdup("")))
		return (-1);
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static char		*backup[OPEN_MAX];
	char			buf[BUFFER_SIZE + 1];
	int				read_size;
	char			*temp;
	int				error;

	if ((fd < 0) || (line == 0) || (BUFFER_SIZE < 1))
		return (-1);
	while ((read_size = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[read_size] = '\0';
		temp = backup[fd];
		if (!(backup[fd] = ft_strjoin(backup[fd], buf)))
			return (-1);
		if (temp)
			free(temp);
		if ((error = isnewline(&backup[fd], line)))
			return (1);
		else if (error == -1)
			return (-1);
	}
	return (backup_clean(&backup[fd], line, read_size));
}
