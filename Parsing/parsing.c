/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 21:32:14 by mlavry            #+#    #+#             */
/*   Updated: 2025/06/26 21:38:09 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	is_exit_no_arg(t_cmd *cmd)
{
	if (ft_strcmp(cmd->name, "exit") == 0 && !(cmd->args[1]))
		return (true);
	return (false);
}

static void	free_line_expand(t_data *data)
{
	free(data->expand_hd);
	free(data->line);
	data->line = NULL;
	data->expand_hd = NULL;
}

static bool	do_tokenization(t_data *data)
{
	replace_dollars(data);
	if (!tokenize(data))
	{
		free_line_expand(data);
		return (false);
	}
	set_token_prev_links(data->token);
	if (!validate_tokens(data->token))
	{
		free_token(&data->token);
		free_line_expand(data);
		return (false);
	}
	return (true);
}

static bool	build_commands(t_data *data)
{
	int		saved;
	t_cmd	*last;

	saved = g_exit_status;
	g_exit_status = 0;
	data->cmd = tokens_to_commands(data, data->token);
	if (!data->cmd)
	{
		free_token(&data->token);
		free_line_expand(data);
		return (false);
	}
	last = data->cmd;
	while (last && last->next)
		last = last->next;
	if (is_exit_no_arg(last) && g_exit_status == 0)
		g_exit_status = saved;
	return (true);
}

bool	parse_line(t_data *data)
{
	if (open_quote(data->line))
	{
		free(data->line);
		data->line = NULL;
		return (false);
	}
	mark_heredoc_quotes(data);
	data->hd_idx = 0;
	if (!do_tokenization(data))
		return (false);
	if (!build_commands(data))
		return (false);
	return (true);
}
