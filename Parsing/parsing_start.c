/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_start.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:55:39 by mlavry            #+#    #+#             */
/*   Updated: 2025/05/29 15:19:40 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_token_prev_links(t_token *tokens)
{
	t_token *prev = NULL;
	while (tokens)
	{
		tokens->prev = prev;
		prev = tokens;
		tokens = tokens->next;
	}
}


bool	parse_line(t_data *data)
{
	if (open_quote(data, data->line))
	{
		free(data->line);
		return (false);
	}
	replace_dollars(data);
	if (!tokenize(data, data->line))
	{
		free(data->line);
		return (false);
	}
	set_token_prev_links(data->token);
	data->cmd = tokens_to_commands(data->token, data);
	if (!(data->cmd))
	{
		free(data->line);
		return (false);
	}
	//print_cmds(data->cmd);
	return (true);
}
