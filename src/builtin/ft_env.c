/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:38:54 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/19 19:49:20 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_env(char **env, t_token *token)
{
	int i = 0;
	if (env == NULL || *env == NULL)
		return (FAIL);
	if (token != NULL || token->next->token_type != PIPE)
	{
		while (token != NULL || token->next->token_type != PIPE)
			token = token->next;
		return (FAIL);
	}
	while (env[i])
		printf("%s\n", env[i++]);
	return (SUCCESS);
}
