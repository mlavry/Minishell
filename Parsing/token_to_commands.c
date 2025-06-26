/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:28:02 by mlavry            #+#    #+#             */
/*   Updated: 2025/06/26 20:27:02 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_output(t_token **tokens, t_cmd **cur)
{
	if (!cur || !*cur)
		return (0);
	if ((*cur)->args == NULL && (*cur)->name == NULL)
	{
		(*cur)->fd_in = STDIN_FILENO;
		(*cur)->fd_out = STDOUT_FILENO;
	}
	if ((*tokens)->next && (*tokens)->next->type == ARG)
	{
		if ((*cur)->fd_out != STDOUT_FILENO && (*cur)->fd_out != -1)
			close((*cur)->fd_out);
		(*cur)->fd_out = open((*tokens)->next->str,
				O_CREAT | O_WRONLY | O_TRUNC | __O_CLOEXEC, 0644);
		if ((*cur)->fd_out < 0)
		{
			perror((*tokens)->next->str);
			return (0);
		}
		*tokens = (*tokens)->next;
	}
	return (1);
}

int	handle_input(t_token **tokens, t_cmd **cur)
{
	if (!cur || !*cur)
		return (0);
	if ((*tokens)->next && (*tokens)->next->type == ARG)
	{
		if ((*cur)->fd_in != STDIN_FILENO)
			close((*cur)->fd_in);
		(*cur)->fd_in = open((*tokens)->next->str, O_RDONLY | __O_CLOEXEC);
		if ((*cur)->fd_in < 0)
		{
			perror((*tokens)->next->str);
			return (0);
		}
		*tokens = (*tokens)->next;
	}
	return (1);
}

int	handle_append(t_token **tokens, t_cmd **cur)
{
	if (!cur || !*cur)
		return (0);
	if ((*tokens) && (*tokens)->type == APPEND
		&& (*tokens)->next && (*tokens)->next->type == ARG)
	{
		if ((*cur)->fd_out != STDOUT_FILENO && (*cur)->fd_out != -1)
			close((*cur)->fd_out);
		(*cur)->fd_out = open((*tokens)->next->str,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if ((*cur)->fd_out < 0)
		{
			perror((*tokens)->next->str);
			return (0);
		}
		*tokens = (*tokens)->next->next;
	}
	return (1);
}

static bool	is_type_token(t_data *data, t_token **toke, t_cmd **hd, t_cmd **cur)
{
	t_token	*tok;

	tok = *toke;
	if (!tok)
		return (false);
	if (tok->type == HEREDOC)
		return (handle_heredoc_type(data, tok, toke, cur));
	else if (tok->type == OUTPUT)
		return (handle_output(toke, cur));
	else if (tok->type == APPEND)
		return (handle_append(toke, cur));
	else if (tok->type == INPUT)
		return (handle_input(toke, cur));
	else if (tok->type == PIPE)
		return (handle_pipe(data, toke, cur));
	else if (tok->type == CMD)
		return (handle_cmd_type(tok, hd, cur, toke));
	else if (tok->type == ARG && handle_redirectarg_type(tok, toke))
		return (true);
	else if (tok->type == ARG)
		return (handle_arg_type(tok, *cur, toke));
	return (true);
}

t_cmd	*tokens_to_commands(t_data *data, t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*cur;

	head = NULL;
	cur = NULL;
	if (tokens && (tokens->type == OUTPUT || tokens->type == INPUT
			|| tokens->type == APPEND || tokens->type == HEREDOC))
	{
		cur = create_new_cmd();
		if (!cur)
			return (free_cmd(&head), NULL);
		head = cur;
	}
	while (tokens && g_exit_status != 130)
	{
		if (!is_type_token(data, &tokens, &head, &cur))
			return (free_cmd(&head), NULL);
	}
	return (head);
}
