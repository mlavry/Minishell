/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:41:00 by mlavry            #+#    #+#             */
/*   Updated: 2025/06/17 02:08:23 by mlavry           ###   ########.fr       */
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

void	add_token(t_token **head, char *value)
{
	t_token	*new;
	t_token	*tmp;

	new = malloc(sizeof(t_token));
	if (!new)
		return ;
	new->str = ft_strdup(value);
	new->type = get_token_type(new->str);
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
}

void	parse_token(t_data *data, char **tokens)
{
	int		i;
	t_token	*token_list;

	token_list = NULL;
	i = 0;
	while (tokens[i])
	{
		add_token(&token_list, tokens[i]);
		i++;
	}
	data->token = token_list;
	mark_commands(data);
	// t_token *tmp = token_list;
 	// while (tmp)
	// {
	// 	printf("Token: %-15s | Type: %-2d\n",
	// 	tmp->str, tmp->type);
	// 	tmp = tmp->next;
	// }
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
	parse_token(data, token);
	free_tab(token);
	return (1);
}
