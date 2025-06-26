/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:48:09 by mlavry            #+#    #+#             */
/*   Updated: 2025/06/25 20:57:33 by mlavry           ###   ########.fr       */
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

void	free_heredoc_file(char *file)
{
	if (file)
	{
		unlink(file);
		free(file);
	}
}

void	free_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;
	t_cmd	*current;

	if (!cmd || !*cmd)
		return ;
	current = *cmd;
	while (current)
	{
		tmp = current->next;
		if (current->name)
			free(current->name);
		if (current->fd_in != STDIN_FILENO && current->fd_in > 2)
			close(current->fd_in);
		if (current->fd_out != STDOUT_FILENO && current->fd_out > 2)
			close(current->fd_out);
		if (current->args)
			free_tab(current->args);
		if (current->heredoc_file)
			free_heredoc_file(current->heredoc_file);
		free(current);
		current = tmp;
	}
	*cmd = NULL;
}
