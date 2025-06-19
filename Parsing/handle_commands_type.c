/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands_type.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:34:37 by aboutale          #+#    #+#             */
/*   Updated: 2025/06/16 23:58:50 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

 bool	handle_heredoc_type(t_token *t, t_token **tok, t_cmd *cur)
{
	if (!t->next || t->next->type != ARG)
	{
		ft_putstr_fd("shel: syntax error near unexpected token `newline'\n", 2);
		g_exit_status = 2;
		return (false);
	}
	if (!handle_heredoc(tok, cur))
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
