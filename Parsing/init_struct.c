/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 19:51:27 by mlavry            #+#    #+#             */
/*   Updated: 2025/06/25 19:24:31 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* static void	init_token(t_token *token)
{
	token->str = NULL;
	token->type = 0;
	token->sq = false;
	token->dq = false;
	token->next = NULL;
	token->prev = NULL;
}

static void	init_cmd(t_cmd *cmd)
{
	cmd->name = NULL;
	cmd->args = NULL;
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	cmd->next = NULL;
} */

void	init_data(t_data *data, int argc, char **argv, char **envp)
{
	ft_bzero(data, sizeof(t_data));
	(void)envp;
	(void)argc;
	(void)argv;
	data->nb_hd = 0;
	data->hd_idx = 0;
	data->expand_hd = NULL;
	data->env = NULL;
	data->cmd = NULL;
	data->token = NULL;
	data->line = NULL;
	g_exit_status = 0;
}
