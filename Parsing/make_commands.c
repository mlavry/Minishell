/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 22:08:30 by mlavry            #+#    #+#             */
/*   Updated: 2025/06/27 00:42:37 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_redir(int type)
{
	return (type == HEREDOC || type == INPUT
		|| type == OUTPUT || type == APPEND);
}

void	mark_commands(t_data *data)
{
	t_token	*prev;
	t_token	*curr;

	prev = NULL;
	curr = data->token;
	while (curr)
	{
		if (curr->type == ARG)
		{
			if (!prev || prev->type == PIPE)
				curr->type = CMD;
		}
		prev = curr;
		curr = curr->next;
	}
}

static int	arg_count(char **args)
{
	int	i;

	i = 0;
	while (args && args[i])
		i++;
	return (i);
}

static char	**ft_grow(char **old, int size)
{
	char	**new;
	int		i;

	i = -1;
	new = malloc(sizeof(char *) * (size + 2));
	if (!new)
		return (NULL);
	while (++i < size)
		new[i] = old[i];
	new[i] = NULL;
	new[i + 1] = NULL;
	free(old);
	return (new);
}

int	add_args(char ***args, char *str)
{
	char	**tmp;
	int		nb;

	if (!*args)
	{
		*args = malloc(sizeof(char *) * 2);
		if (!*args)
			return (0);
		(*args)[0] = ft_strdup(str);
		if (!(*args)[0])
			return (free(*args), 0);
		(*args)[1] = NULL;
		return (1);
	}
	nb = arg_count(*args);
	tmp = ft_grow(*args, nb);
	if (!tmp)
		return (0);
	tmp[nb] = ft_strdup(str);
	if (!tmp[nb])
		return (free(tmp), 0);
	tmp[nb + 1] = NULL;
	*args = tmp;
	return (1);
}
