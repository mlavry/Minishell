/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands_type.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:34:37 by aboutale          #+#    #+#             */
/*   Updated: 2025/06/12 18:34:39 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	handle_heredoc_type(t_token *t, t_token **tok, t_cmd *cur, t_data *data)
{
	if (!t->next || t->next->type != ARG)
	{
		ft_putstr_fd("shel: syntax error near unexpected token `newline'\n", 2);
		data->exit_code = 2;
		return (false); // ✨ très important
	}
	if (!handle_heredoc(tok, cur))
		return (false);
	*tok = (*tok)->next->next; // HEREDOC + ARG
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


