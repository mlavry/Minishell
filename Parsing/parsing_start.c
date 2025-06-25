/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_start.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:55:39 by mlavry            #+#    #+#             */
/*   Updated: 2025/06/25 21:27:15 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	set_token_prev_links(t_token *tokens)
{
	t_token	*prev;

	prev = NULL;
	while (tokens)
	{
		tokens->prev = prev;
		prev = tokens;
		tokens = tokens->next;
	}
}

bool	check_redirection_syntax(t_token *tok)
{
	if (!tok->next || tok->next->type != ARG)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		if (!tok->next)
			ft_putstr_fd("newline", 2);
		else
			ft_putstr_fd(tok->next->str, 2);
		ft_putstr_fd("'\n", 2);
		g_exit_status = 2;
		return (false);
	}
	return (true);
}

bool	check_pipe_syntax(t_token *tok)
{
	if (!tok->prev || !tok->next)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		g_exit_status = 2;
		return (false);
	}
   // Optionnel : vérifier que tokens->prev et tokens->next ne sont pas PIPE ou opérateurs
	if (tok->prev->type == PIPE || tok->next->type == PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		g_exit_status = 2;
		return (false);
	}
	return (true);
}

bool	validate_tokens(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == OUTPUT || tokens->type == INPUT
			|| tokens->type == APPEND || tokens->type == HEREDOC)
		{
			if (!check_redirection_syntax(tokens))
				return (false);
		}
		else if (tokens->type == PIPE)
		{
			if (!check_pipe_syntax(tokens))
				return (false);
		}
		tokens = tokens->next;
	}
	return (true);
}

bool	parse_line(t_data *data)
{
	if (open_quote(data->line))
	{
		free(data->line);
		return (false);
	}
	mark_heredoc_quotes(data);
	data->hd_idx = 0;
	replace_dollars(data);
	if (!tokenize(data))
	{
		free(data->line);
		return (false);
	}
	set_token_prev_links(data->token);
	if (!validate_tokens(data->token))
	{
		free(data->line);
		free_token(&data->token);
		return (false);
	}
	data->cmd = tokens_to_commands(data, data->token);
	if (!(data->cmd))
	{
		free(data->line);
		free(data->expand_hd);
		free_token(&data->token);
		return (false);
	}
	return (true);
}
