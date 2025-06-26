/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:48:09 by mlavry            #+#    #+#             */
/*   Updated: 2025/06/26 21:28:38 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_all(t_data *data, int exit_code, bool exit_or_not)
{
	if (data->env)
		free_env(&data->env);
	if (data->token)
		free_token(&data->token);
	if (data->cmd)
	{
		free_cmd(&data->cmd);
		data->cmd = NULL;
	}
	if (data->line)
	{
		free(data->line);
		data->line = NULL;
	}
	if (data->expand_hd)
	{
		free(data->expand_hd);
		data->expand_hd = NULL;
	}
	if (exit_or_not)
	{
		clear_history();
		exit(exit_code);
	}
}

void	malloc_failed(t_data *data)
{
	close_all_fd();
	ft_putstr_fd("Cannot allocate memory\n", 2);
	free_all(data, 1, true);
}
