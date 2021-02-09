/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 20:20:29 by ulee              #+#    #+#             */
/*   Updated: 2020/11/22 17:08:04 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		is_set(char const *s1, char const *set)
{
	int		check;

	check = 0;
	while (*set)
	{
		set++;
		if (*s1 == *set)
		{
			check = 1;
			break ;
		}
	}
	return (check);
}

int		cut_front(char const *s1, char const *set, int len)
{
	int check;
	int i;
	int j;
	int start;

	start = 0;
	i = 0;
	check = 0;
	while (i < len)
	{
		check = 0;
		j = 0;
		if (s1[i] == set[j])
			check = 1;
		else
			check = is_set(&s1[i], &set[j]);
		if (check)
			start = ++i;
		else
			break ;
	}
	return (start);
}

int		cut_back(char const *s1, char const *set, int len)
{
	int		check;
	int		i;
	int		j;
	int		end;

	end = 0;
	i = len;
	check = 0;
	while (i >= 0)
	{
		check = 0;
		j = 0;
		if (s1[i] == set[j])
			check = 1;
		else
			check = is_set(&s1[i], &set[j]);
		if (check)
			end = --i;
		else
			break ;
	}
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*dst;
	int		len;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup(s1));
	len = ft_strlen(s1);
	start = 0;
	end = len;
	start = cut_front(s1, set, len);
	end = cut_back(s1, set, len);
	if (start >= end)
		return (ft_strdup(""));
	len = end - start + 2;
	if (!(dst = (char *)malloc(sizeof(char) * len)))
		return (0);
	ft_strlcpy(dst, &s1[start], len);
	return (dst);
}
