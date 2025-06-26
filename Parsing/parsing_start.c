/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_start.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:55:39 by mlavry            #+#    #+#             */
/*   Updated: 2025/06/25 19:24:59 by mlavry           ###   ########.fr       */
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

static bool	is_exit_no_arg(t_cmd *cmd)
{
	if (ft_strcmp(cmd->name, "exit") == 0 && !(cmd->args[1]))
		return (true);
	return (false);
}

bool	parse_line(t_data *data)
{
	int		saved_status;
	t_cmd	*last;

	if (open_quote(data->line))
	{
		free(data->line);
		data->line = NULL;
		return (false);
	}
	mark_heredoc_quotes(data);
	data->hd_idx = 0;
	replace_dollars(data);
	if (!tokenize(data))
	{
		free(data->expand_hd);
		free(data->line);
		data->line = NULL;
		data->expand_hd = NULL;
		return (false);
	}
	set_token_prev_links(data->token);
	if (!validate_tokens(data->token))
	{
		free(data->expand_hd);
		free(data->line);
		free_token(&data->token);
		data->line = NULL;
		data->expand_hd = NULL;
		return (false);
	}
	saved_status = g_exit_status;
	g_exit_status = 0;
	data->cmd = tokens_to_commands(data, data->token);
	if (!(data->cmd))
	{
		free(data->line);
		free(data->expand_hd);
		free_token(&data->token);
		data->line = NULL;
		data->expand_hd = NULL;
		return (false);
	}
	last = data->cmd;
	while (last && last->next)
		last = last->next;
	if (is_exit_no_arg(last) && g_exit_status == 0)
		g_exit_status = saved_status;
	return (true);
}
