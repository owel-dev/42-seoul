/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 20:20:32 by ulee              #+#    #+#             */
/*   Updated: 2021/02/15 04:58:13 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *str, unsigned int start_index, size_t cut_size)
{
	char	*result;

	if (str == NULL)
		return (NULL);
	if (ft_strlen(str) < start_index)
		return (ft_strdup(""));
	result = malloc(sizeof(char) * (cut_size + 1));
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, str + start_index, cut_size + 1);
	return (result);
}
