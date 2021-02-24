/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 21:05:34 by ulee              #+#    #+#             */
/*   Updated: 2021/01/21 01:27:13 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	isnewline(char **backup, char **line)
{
	char	*newline;
	char	*temp;

	newline = ft_strchr(*backup, '\n');
	if (newline == NULL)
		return (0);
	*newline = '\0';
	*line = ft_strdup(*backup);
	if (*line == NULL)
		return (-1);
	temp = ft_strdup(++newline);
	if (temp == NULL)
		return (-1);
	free(*backup);
	*backup = temp;
	return (1);
}

int	backup_clean(char **backup, char **line, int read_size)
{
	if (read_size < 0)
		return (-1);
	if (*backup != NULL && (isnewline(backup, line)))
		return (1);
	else if (*backup != NULL)
	{
		*line = ft_strdup(*backup);
		if (*line == NULL)
			return (-1);
		free(*backup);
		*backup = NULL;
		return (0);
	}
	*line = ft_strdup("");
	if (*line == NULL)
		return (-1);
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char		*backup[OPEN_MAX];
	char			buf[BUFFER_SIZE + 1];
	int				read_size;
	int				error;

	if ((fd < 0) || (line == 0) || (BUFFER_SIZE < 1))
		return (-1);
	read_size = read(fd, buf, BUFFER_SIZE);
	while (read_size > 0)
	{
		buf[read_size] = '\0';
		backup[fd] = ft_strjoin(backup[fd], buf);
		if (backup[fd] == NULL)
			return (-1);
		error = isnewline(&backup[fd], line);
		if (error == 1)
			return (1);
		else if (error == -1)
			return (-1);
		read_size = read(fd, buf, BUFFER_SIZE);
	}
	return (backup_clean(&backup[fd], line, read_size));
}
