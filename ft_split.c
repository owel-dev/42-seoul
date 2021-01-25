/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 20:19:51 by ulee              #+#    #+#             */
/*   Updated: 2020/11/22 16:08:32 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**split_free(char **result)
{
	int i;

	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
	free(result);
	return (NULL);
}

int		word_count(const char *s, char c)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			len++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (len);
}

char	*cut_word(const char *s, char c, int order)
{
	int		start;
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			count++;
			if (count == order)
			{
				start = i;
				while (s[i] && s[i] != c)
					i++;
				return (ft_substr(s, start, i - start));
			}
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	char	*word;
	int		i;
	int		len;

	if (s == NULL)
		return (NULL);
	len = word_count(s, c);
	if (!(result = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	result[len] = NULL;
	i = 0;
	while (i < len)
	{
		if (!(word = cut_word(s, c, i + 1)))
			return (split_free(result));
		result[i] = word;
		i++;
	}
	return (result);
}
