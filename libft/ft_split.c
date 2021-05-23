/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 20:19:51 by ulee              #+#    #+#             */
/*   Updated: 2021/05/19 11:27:19 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**all_free(char **result)
{
	int		i;

	i = 0;
	while (result[i] != NULL)
	{
		free(result[i]);
		result[i] = NULL;
		i++;
	}
	free(result);
	result = NULL;
	return (NULL);
}

int		count_words(const char *str, char c)
{
	int		i;
	int		word_count;

	i = 0;
	word_count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			i++;
		else
		{
			word_count++;
			while (str[i] != '\0' && str[i] != c)
				i++;
		}
	}
	return (word_count);
}

char	*cut_word(const char *str, char c, int word_number)
{
	int		start;
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			i++;
		else
		{
			count++;
			if (count == word_number)
			{
				start = i;
				while (str[i] && str[i] != c)
					i++;
				return (ft_substr(str, start, i - start));
			}
			while (str[i] && str[i] != c)
				i++;
		}
	}
	return (NULL);
}

char	**ft_split(char const *str, char c)
{
	char	**result;
	int		word_count;
	char	*word;
	int		i;

	if (str == NULL)
		return (NULL);
	word_count = count_words(str, c);
	result = (char **)calloc(sizeof(char *), (word_count + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < word_count)
	{
		word = cut_word(str, c, i + 1);
		if (word == NULL)
			return (all_free(result));
		result[i] = word;
		i++;
	}
	return (result);
}
