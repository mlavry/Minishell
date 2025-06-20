/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:33:00 by aboutale          #+#    #+#             */
/*   Updated: 2025/06/17 00:01:51 by mlavry           ###   ########.fr       */
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

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->fd_in = STDIN_FILENO;
	cmd->fd_out = STDOUT_FILENO;
	cmd->next = NULL;
	return (cmd);
}



bool is_redirection(int type)
{
	return (type == OUTPUT || type == APPEND || type == INPUT || type == HEREDOC);
}

int handle_redirect_after_pipe(t_token **tokens, t_cmd **cur)
{
	while (*tokens && is_redirection((*tokens)->type))
	{
		int type = (*tokens)->type;

		if (type == OUTPUT)
		{
			if (!handle_output(tokens, cur))
				return (0);
		}
		else if (type == APPEND)
		{
			if (!handle_append(tokens, cur))
				return (0);
		}
		else if (type == INPUT)
		{
			if (!handle_input(tokens, cur))
				return (0);
		}
		else if (type == HEREDOC)
		{
			if (!handle_heredoc_type(*tokens, tokens, *cur))
				return (0);
		}
	}
	return (1);
}

/* int handle_pipe(t_token **tokens, t_cmd **cur)
{
	if (!cur || !*cur)
		return (0);
	if ((*tokens)->type == PIPE && (!(*tokens)->next))
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (0);
	}

	*tokens = (*tokens)->next;
	if (*tokens && is_redirection((*tokens)->type))
	{
		if (!*cur)
			*cur = create_new_cmd();
		if (!handle_redirect_after_pipe(tokens, cur))
			return (0);
	}
	return (1);
} */




int	handle_pipe(t_token **tokens, t_cmd **cur)
{
	if (!cur || !*cur)
		return (0);
	if ((*tokens)->type == PIPE && (!(*tokens)->next))
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (0);
	}

	*tokens = (*tokens)->next;
	if (*tokens && is_redirection((*tokens)->type))
	{
    	if (!*cur)
        	*cur = create_new_cmd(); // Crée un t_cmd vide

    	if (handle_redirect_after_pipe(tokens, cur))
			return 0;
	}

/* 	if (!cur || !*cur)
		return (0); */
	return (1);
}


int	handle_output(t_token **tokens, t_cmd **cur)
{
	if (!cur || !*cur)
		return (0);
	if ((*cur)->args == NULL && (*cur)->name == NULL)
	{
		(*cur)->name = ft_strdup(""); // pour signaler que ce t_cmd existe
		(*cur)->fd_in = STDIN_FILENO;
		(*cur)->fd_out = STDOUT_FILENO;
	}	
	if (((*tokens)->type == OUTPUT || (*tokens)->type == APPEND || (*tokens)->type == INPUT || (*tokens)->type == HEREDOC)
		&& (!(*tokens)->next || (*tokens)->next->type != ARG))
	{
		ft_putstr_fd("shel: syntax error near unexpected token `newline'\n", 2);
		g_exit_status = 2;
		return (0);
	}
	if ((*tokens)->next && (*tokens)->next->type == ARG)
	{
		if ((*cur)->fd_out != STDOUT_FILENO && (*cur)->fd_out != -1)
			close((*cur)->fd_out);
		(*cur)->fd_out = open((*tokens)->next->str,
				O_CREAT | O_WRONLY | O_TRUNC | __O_CLOEXEC, 0644);
		if ((*cur)->fd_out < 0)
		{
			printf("%s: No such file or directory\n", (*tokens)->next->str);
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
	if (tokens && ((*tokens)->type == INPUT)
		&& (!(*tokens)->next || (*tokens)->next->type != ARG))
	{
		ft_putstr_fd("shel: syntax error near unexpected token `newline'\n", 2);
		g_exit_status = 2;
		return (0);
	}
	if ((*tokens)->next && (*tokens)->next->type == ARG)
	{
		if ((*cur)->fd_in != STDIN_FILENO)
			close((*cur)->fd_in);
		(*cur)->fd_in = open((*tokens)->next->str, O_RDONLY | __O_CLOEXEC);
		if ((*cur)->fd_in < 0)
		{
			printf("%s: No such file or directory\n", (*tokens)->next->str);
			return (0);
		}

		*tokens = (*tokens)->next;
	}
	return (1);
}
