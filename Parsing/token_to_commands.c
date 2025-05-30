/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:28:02 by mlavry            #+#    #+#             */
/*   Updated: 2025/05/29 15:19:29 by mlavry           ###   ########.fr       */
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

int	handle_pipe(t_token **tokens, t_cmd **cur)
{

	if ((*tokens)->type == PIPE && (!(*tokens)->next))
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (0);
	}
	if (!cur || !*cur)
		return (0);
	return (1);
}

int	handle_output(t_token **tokens, t_cmd **cur, t_data *data)
{
	if ((*tokens)->type == OUTPUT
		&& (!(*tokens)->next || (*tokens)->next->type != ARG))
	{
		data->exit_code = 2;
		return (0);
	}
	if ((*tokens)->next && (*tokens)->next->type == ARG)
	{
		(*cur)->fd_out = open((*tokens)->next->str,
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if ((*cur)->fd_out < 0)
		{
			perror("open");
			return (0);
		}
		*tokens = (*tokens)->next;
	}
	return (1);
}

int	handle_input(t_token **tokens, t_cmd **cur, t_data *data)
{
	if ((*tokens)->type == INPUT
		&& (!(*tokens)->next || (*tokens)->next->type != ARG))
	{
		data->exit_code = 2;
		return (0);
	}
	if ((*tokens)->next && (*tokens)->next->type == ARG)
	{
		(*cur)->fd_in = open((*tokens)->next->str, O_RDONLY);
		if ((*cur)->fd_in < 0)
		{
			perror("open");
			return (0);
		}
		*tokens = (*tokens)->next;
	}
	return (1);
}


int	handle_append(t_token **tokens, t_cmd **cur, t_data *data)
{

	if ((*tokens)->type == APPEND
		&& ( !(*tokens)->prev || !(*tokens)->next || (*tokens)->next->type != ARG))
	{
		data->exit_code = 2;
		return (0);
	}
    if ((*tokens) && (*tokens)->type == APPEND
		&& (*tokens)->next && (*tokens)->next->type == ARG)
	{
		(*cur)->fd_out = open((*tokens)->next->str,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if ((*cur)->fd_out < 0)
		{
			perror("open");
			return (0);
		}
		*tokens = (*tokens)->next;
	}
	return (1);
} 

bool	is_type_token(t_token **tokens, t_cmd **head, t_cmd **cur, t_data *data)
{
	if ((*tokens)->type == CMD)
		return (handle_cmd(head, cur, *tokens));
	if ((*tokens)->type == ARG)
		return (handle_arg(*cur, *tokens));
	if ((*tokens)->type == OUTPUT)
		return (handle_output(tokens, cur, data));
	if ((*tokens)->type == INPUT)
		return (handle_input(tokens, cur, data));
	if ((*tokens)->type == PIPE)
		return (handle_pipe(tokens,cur));
	/* if ((*tokens)->type == HEREDOC)
        return(handle_heredoc(cur)); */
	if ((*tokens)->type == APPEND)
        return (handle_append(tokens ,cur, data)); 
	return (true);
}

t_cmd	*tokens_to_commands(t_token *tokens, t_data *data)
{
	t_cmd	*head;
	t_cmd	*cur;

	head = NULL;
	cur = NULL;
/* 	if (tokens && (tokens->type == OUTPUT || tokens->type == INPUT || tokens->type == APPEND))
	{
    	printf("minishell: syntax error near unexpected token `%s'\n", tokens->str);
   	 	data->exit_code = 2;
    	return (0); // empêche l’exécution
	} */
	while (tokens)
	{
		if (!is_type_token (&tokens, &head, &cur, data))
			return (NULL);
		tokens = tokens->next;
	}
	return (head);
}

/* void print_cmds(t_cmd *c)
{
    int idx;
    while (c)
    {
        printf("=== Command: %s ===\n", c->name);
        for (idx = 0; c->args && c->args[idx]; idx++)
            printf("  arg[%d]: %s\n", idx, c->args[idx]);
        printf("  fd_in = %d, fd_out = %d\n", c->fd_in, c->fd_out);
        c = c->next;
    }
} */
