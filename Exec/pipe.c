/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:20:22 by aboutale          #+#    #+#             */
/*   Updated: 2025/06/26 20:56:56 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	setup_outandin(t_cmd *cmd, int prev_fd, int *pipe_fd)
{
	if (cmd->fd_in != STDIN_FILENO)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	else if (prev_fd != -1)
		dup2(prev_fd, STDIN_FILENO);
	if (cmd->fd_out != STDOUT_FILENO)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
	else if (cmd->next)
		dup2(pipe_fd[1], STDOUT_FILENO);
	if (cmd->next && pipe_fd[0] != -1)
		close(pipe_fd[0]);
	if (cmd->next || cmd->fd_out == STDOUT_FILENO)
		close(pipe_fd[1]);
	if (prev_fd != -1)
		close(prev_fd);
	if (cmd->next)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
}

bool	is_empty_cmd(t_cmd *cmd)
{
	return (!cmd || !cmd->args || !cmd->args[0]);
}

void	builtin_in_pipe(t_data *data, t_cmd *original_cmd_head)
{
	if (data->cmd && data->cmd->args && data->cmd->args[0]
		&& ft_strcmp(data->cmd->args[0], "exit") == 0)
	{
		data->cmd = original_cmd_head;
		free_all(data, g_exit_status, true);
		exit(0);
	}
	exec_builtin(data);
	data->cmd = original_cmd_head;
	free_all(data, g_exit_status, true);
	exit(0);
}

void	exec_command(t_cmd *cmd, t_data *data)
{
	char	*path;
	char	**envi;
	t_cmd	*original_cmd_head;

	original_cmd_head = data->cmd;
	if (!cmd || !cmd->args || !cmd->args[0])
		free_all(data, 0, true);
	data->cmd = cmd;
	if (isbuiltin(data))
		builtin_in_pipe(data, original_cmd_head);
	data->cmd = original_cmd_head;
	path = getpath(cmd->args[0], data);
	if (!path)
		handle_command_error(cmd->args[0], "command not found\n", 127, data);
	reset_signals_to_default();
	envi = convert_env(data, data->env);
	if (execve(path, cmd->args, envi) == -1)
	{
		close_all_fd();
		perror("execve");
		free(path);
		free_all(data, g_exit_status, true);
		exit(127);
	}
}

void	parent(t_cmd *current_cmd, int *prev_fd, int *pipe_fd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (current_cmd->next)
	{
		close(pipe_fd[1]);
		*prev_fd = pipe_fd[0];
	}
	if (current_cmd->fd_in > 2)
		close(current_cmd->fd_in);
	if (current_cmd->fd_out > 2)
		close(current_cmd->fd_out);
}
