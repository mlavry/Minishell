/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:41:00 by mlavry            #+#    #+#             */
/*   Updated: 2025/06/26 19:26:50 by mlavry           ###   ########.fr       */
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

static void	check_value(t_token *token)
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

int	add_token(t_token **head, char *value)
{
	t_token	*new;
	t_token	*tmp;

	new = malloc(sizeof(t_token));
	if (!new)
		return (0);
	new->str = ft_strdup(value);
	if (!new->str)
		return (free(new), 0);
	new->type = get_token_type(new->str);
	if (!check_arg_op_syntax(new))
	{
		free(new->str);
		free(new); 
		return (0);
	}
	check_value(new);
	new->next = NULL;
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
		if (!add_token(&token_list, tokens[i]))
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
