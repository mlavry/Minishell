/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:48:09 by mlavry            #+#    #+#             */
/*   Updated: 2025/06/19 16:33:34 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_all(t_data *data, int exit_code, bool exit_or_not)
{
	free_env(&data->env);
	free_token(&data->token);
	free_cmd(&data->cmd);
	if (data->line)
	{
		free(data->line);
		data->line = NULL;
	}
	if (exit_or_not)
	{
		clear_history();
		exit(exit_code);
	}
}

void	malloc_failed(t_data *data)
{
	ft_putstr_fd("Cannot allocate memory\n", 2);
	free_all(data, 1, true);
}
