/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:41:00 by mlavry            #+#    #+#             */
/*   Updated: 2025/04/22 22:42:34 by mlavry           ###   ########.fr       */
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

void	add_token(t_token **head, char *value, int type)
{
	t_token	*new;
	t_token	*tmp;

	new = malloc(sizeof(t_token));
	if (!new)
		return ;
	new->str = ft_strdup(value);
	new->type = type;
	new->next = NULL;
	new->sq = false;
	new->dq = false;
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
	int		type;

	token_list = NULL;
	i = 0;
	while (tokens[i])
	{
		type = get_token_type(tokens[i]);
		add_token(&token_list, tokens[i], type);
		i++;
	}
	t_token *tmp = token_list;
	while (tmp)
	{
		printf("Token: %-15s | Type: %-2d | SQ: %d | DQ: %d\n", 
			tmp->str, tmp->type, tmp->sq, tmp->dq);
		tmp = tmp->next;
	}
	data->token = token_list;
}

int	tokenize(t_data *data, char *line)
{
	char	**token;

	token = line_to_token(line);
	if (!token)
	{
		data->exit_code = 2;
		return (0);
	}
	parse_token(data, token);
	return (1);
}
