/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 22:08:30 by mlavry            #+#    #+#             */
/*   Updated: 2025/04/29 22:48:36 by mlavry           ###   ########.fr       */
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
