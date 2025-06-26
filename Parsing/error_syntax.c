/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 21:48:29 by aboutale          #+#    #+#             */
/*   Updated: 2025/06/26 21:48:32 by aboutale         ###   ########.fr       */
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

void	check_value(t_token *token)
{
	int		i;
	char	type_quote;
	char	*res;

	i = 1;
	if (is_quoted(token->str[0]) && is_operator(token->str[1]))
	{
		type_quote = token->str[0];
		while (is_operator(token->str[i]))
			i++;
		if (token->str[i] == type_quote && !(token->str[i + 1]))
		{
			res = ft_substr(token->str, 1, i - 1);
			free(token->str);
			token->str = res;
			token->type = ARG;
		}
	}
}
