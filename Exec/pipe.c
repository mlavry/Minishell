/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:20:22 by aboutale          #+#    #+#             */
/*   Updated: 2025/05/20 17:35:39 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	input_and_output(t_data *data, int prev_fd, int pipe_fd[2])
{
	if (data->cmd->fd_in != STDIN_FILENO)
	{
		dup2(data->cmd->fd_in, STDIN_FILENO);
		close(data->cmd->fd_in);
	}
	else if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (data->cmd->fd_out != STDOUT_FILENO)
	{
		dup2(data->cmd->fd_out, STDOUT_FILENO);
		close(data->cmd->fd_out);
	}
	else if (data->cmd->next)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
}

void	childprocess(t_data *data, int prev_fd, int pipe_fd[2])
{
	input_and_output(data, prev_fd, pipe_fd);
	if (prev_fd != -1)
		close(prev_fd);
	if (data->cmd->next)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	if (isbuiltin(data))
		exec_builtin(data);
	else
		exec_extern_command(data->cmd->args, data->env, data);
	exit(EXIT_SUCCESS);
}

void	parent_process(int *prev_fd, t_cmd **cmd, int *pipe_fd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if ((*cmd)->next)
	{
		close(pipe_fd[1]);
		*prev_fd = pipe_fd[0];
	}
	else
		*prev_fd = -1;
	*cmd = (*cmd)->next;
}

void	handle_error(char *message)
{
	ft_putstr_fd(message, 2);
	exit(EXIT_FAILURE);
}

void	exec_pipe(t_cmd *cmd, t_data *data)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		prev_fd;

	prev_fd = -1;
	while (cmd)
	{
		data->cmd = cmd;
		if (cmd->next && pipe(pipe_fd) == -1)
			handle_error("pipe failed\n");
		pid = fork();
		if (pid == -1)
			handle_error("fork error\n");
		if (pid == 0)
			childprocess(data, prev_fd, pipe_fd);
		else
			parent_process(&prev_fd, &cmd, pipe_fd);
	}
	while (wait(NULL) > 0)
		;
}
