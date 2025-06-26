/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands_type.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:34:37 by aboutale          #+#    #+#             */
/*   Updated: 2025/06/27 00:23:07 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_cmd(t_cmd **head, t_cmd **cur, t_token *tokens)
{
	t_cmd	*new;

	new = ft_calloc (1, sizeof(t_cmd));
	if (!new)
		return (0);
	new->name = ft_strdup(tokens->str);
	if (!new->name)
	{
		free(new);
		return (0);
	}
	new->fd_in = STDIN_FILENO;
	new->fd_out = STDOUT_FILENO;
	if (!add_args(&new->args, new->name))
	{
		free(new->name);
		free(new);
		return (0);
	}
	if (!(*head))
		(*head) = new;
	else
		(*cur)->next = new;
	(*cur) = new;
	return (1);
}

bool	handle_heredoc_type(t_data *data, t_token *t, t_token **tok, t_cmd **c)
{
	if (!t->next || t->next->type != ARG)
		return (false);
	if (*c == NULL)
	{
		*c = create_new_cmd();
		if (!*c)
			return (false);
	}
	if (!handle_heredoc(data, tok, *c))
		return (false);
	*tok = (*tok)->next->next;
	return (true);
}

bool	handle_cmd_type(t_token *tok, t_cmd **hd, t_cmd **cur, t_token **tokens)
{
	bool	ok;

	ok = handle_cmd(hd, cur, tok);
	*tokens = tok->next;
	return (ok);
}

bool	handle_arg_type(t_token *tok, t_cmd *cur, t_token **tokens)
{
	bool	ok;

	ok = handle_arg(cur, tok);
	*tokens = tok->next;
	return (ok);
}

bool	handle_redirectarg_type(t_token *tok, t_token **tokens)
{
	if (tok && tok->prev && tok->prev->type
		&& (tok->prev->type == OUTPUT
			|| tok->prev->type == INPUT
			|| tok->prev->type == APPEND
			|| tok->prev->type == HEREDOC))
	{
		*tokens = tok->next;
		return (true);
	}
	return (false);
}
