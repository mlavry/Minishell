/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_start.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:55:39 by mlavry            #+#    #+#             */
/*   Updated: 2025/05/12 19:29:02 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	parse_line(t_data *data, char *line)
{
	if (open_quote(data, line))
	{
		free(line);
		return (false);
	}
	if (!tokenize(data, line))
	{
		free(line);
		return (false);
	}
	data->cmd = tokens_to_commands(data->token);
	if(!(data->cmd))
	{
		free(line);
		return (false);
	}
	//print_cmds(data->cmd);
	return (true);
}
