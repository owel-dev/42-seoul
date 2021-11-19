/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulee <ulee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:35:44 by hyospark          #+#    #+#             */
/*   Updated: 2021/11/19 19:54:26 by ulee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipe_cmd(t_bundle *bundle, t_token *token)
{
	pid_t	pid;
	int		status;
	int		fd[2];
	t_token *tem;

	pid = fork();
	if (pid < 0)
		print_error("pipe fork error", EXIT_FAILURE);
	pipe(fd);
	if (pipe < 0)
		print_error("pipe function error", EXIT_FAILURE);
	if(pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		return (1);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		tem = token->next;
		token = tem;
		while(token->next->content)
		{
			tem = token->next;
			token = tem;
			if (token->token_type == PIPE)
				break ;
		}
		bundle->token = token->next;
		waitpid(pid ,&status, 0);
		return (0);
	}
}

t_token *check_cmd(t_bundle *bundle)
{
	t_token *ret_token;

	ret_token = is_builtin(bundle, bundle->token);
	if (ret_token)
		return (ret_token);
	ret_token = is_bin(bundle, bundle->token);
	if (ret_token)
		return (ret_token);
	return (NULL);
}

int	execute_cmd(t_bundle *bundle)
{
	int result;
	t_token *temp;
	int	child_ps;

	while (bundle->token)
	{
		if (bundle->token->pipe == PIPE)
			child_ps = pipe_cmd(bundle, bundle->token);
		// if (bundle->token->redir > 0)
		// 	redir_cmd();
		result = check_cmd(bundle);
		if (child_ps)
			return (-1);
		bundle->token = temp->next;
	}
	return (result);
}