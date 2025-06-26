/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:41:00 by mlavry            #+#    #+#             */
/*   Updated: 2025/06/26 22:11:15 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_token_type(char *str)
{
	if (!ft_strcmp(str, "<"))
		return (INPUT);
	if (!ft_strcmp(str, "<<"))
		return (HEREDOC);
	if (!ft_strcmp(str, ">"))
		return (OUTPUT);
	if (!ft_strcmp(str, ">>"))
		return (APPEND);
	if (!ft_strcmp(str, "|"))
		return (PIPE);
	else
		return (ARG);
}

static t_token	*token_new(t_data *data, char *value)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->str = ft_strdup(value);
	if (!new->str)
		return (free(new), NULL);
	new->type = get_token_type(new->str);
	if (!check_arg_op_syntax(new))
	{
		free(new->str);
		return (free(new), NULL);
	}
	check_value(data, new);
	new->next = NULL;
	return (new);
}

int	add_token(t_data *data, t_token **head, char *value)
{
	t_token	*new;
	t_token	*tmp;

	new = token_new(data, value);
	if (!new)
		return (0);
	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (1);
}

int	parse_token(t_data *data, char **tokens)
{
	int		i;
	t_token	*token_list;

	token_list = NULL;
	i = 0;
	while (tokens[i])
	{
		if (!add_token(data, &token_list, tokens[i]))
		{
			free_token(&token_list);
			return (0);
		}
		i++;
	}
	data->token = token_list;
	mark_commands(data);
	return (1);
}

int	tokenize(t_data *data)
{
	char	**token;

	token = line_to_token(data);
	if (!token)
	{
		g_exit_status = 2;
		return (0);
	}
	if (!parse_token(data, token))
	{
		free_tab(token);
		return (0);
	}
	free_tab(token);
	return (1);
}
