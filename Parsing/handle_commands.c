/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:33:00 by aboutale          #+#    #+#             */
/*   Updated: 2025/06/27 00:26:28 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_arg(t_cmd *cur, t_token *token)
{
	if (!cur)
		return (0);
	if (!add_args(&cur->args, token->str))
		return (0);
	return (1);
}

t_cmd	*create_new_cmd(void)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->heredoc_file = NULL;
	cmd->fd_in = STDIN_FILENO;
	cmd->fd_out = STDOUT_FILENO;
	cmd->next = NULL;
	cmd->name = NULL;
	return (cmd);
}

bool	is_redirection(int type)
{
	return (type == OUTPUT || type == APPEND
		|| type == INPUT || type == HEREDOC);
}

int	handle_redirect_after_pipe(t_data *data, t_token **tokens, t_cmd **cur)
{
	while (*tokens && is_redirection((*tokens)->type))
	{
		if ((*tokens)->type == OUTPUT)
		{
			if (!handle_output(tokens, cur))
				return (free_cmd(cur), 0);
		}
		else if ((*tokens)->type == APPEND)
		{
			if (!handle_append(tokens, cur))
				return (0);
		}
		else if ((*tokens)->type == INPUT)
		{
			if (!handle_input(tokens, cur))
				return (0);
		}
		else if ((*tokens)->type == HEREDOC)
		{
			if (!handle_heredoc_type(data, *tokens, tokens, cur))
				return (0);
		}
	}
	return (1);
}

int	handle_pipe(t_data *data, t_token **tokens, t_cmd **cur)
{
	t_cmd	*new_cmd;

	if (!tokens || !*tokens)
		return (0);
	*tokens = (*tokens)->next;
	if (*tokens && is_redirection((*tokens)->type))
	{
		new_cmd = create_new_cmd();
		if (!new_cmd)
			return (0);
		if (*cur)
			(*cur)->next = new_cmd;
		*cur = new_cmd;
		if (!handle_redirect_after_pipe(data, tokens, cur))
			return (0);
	}
	return (1);
}
