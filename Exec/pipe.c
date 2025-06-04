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
void	handle_command_error(char *cmd, char *msg, int exit_code, t_data *data)
{
	if (data)
		data->exit_code = exit_code;
	ft_putstr_fd("minishell: ", 2);
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(msg, 2);
	exit(exit_code);
}

void	childprocess(t_data *data, int prev_fd, int pipe_fd[2])
{

	if (!isbuiltin(data))
	{
		//if (!getpath(data->cmd->args[0], data))
		char *path = getpath(data->cmd->args[0], data);
		if (!path)
			handle_command_error(data->cmd->args[0], "command not found\n",
			127, data);
	} 
	input_and_output(data, prev_fd, pipe_fd);
	if (prev_fd != -1)
		close(prev_fd);
	if (data->cmd->next)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	if (isbuiltin(data))
	{
		if (ft_strcmp(data->cmd->args[0], "exit") == 0)
			exit(0);
		else
			exec_builtin(data);
	}
	else
		exec_extern_command(data->cmd->args, data->env, data);
	exit(EXIT_SUCCESS);
}

void	parent_process(int *prev_fd, t_cmd **cmd, int *pipe_fd, t_data *data)
{
	int	status;

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

	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			data->exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			data->exit_code = 128 + WTERMSIG(status);
	}
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

	while (cmd)
	{
		data->cmd = cmd;
		if (cmd->next && pipe(pipe_fd) == -1)
			handle_error("pipe failed\n");
		pid = fork();
		if (pid == -1)
			handle_error("fork error\n");
		if (pid == 0)
		{
			if (!isbuiltin(data))
			{
				char *path = getpath(cmd->args[0], data);
				if (!path)
					handle_command_error(cmd->args[0], "command not found\n",
						127, data);
			} 
		/* 	if (execve(path, cmd->args,convert_env(data->env)) == -1)
			{
   	 			printf("%s: command not found\n", cmd->args[0]);
    			exit(127);
			}   */
			childprocess(data, prev_fd, pipe_fd);
		}
		else
			parent_process(&prev_fd, &cmd, pipe_fd, data);
	}
	while (wait(NULL) > 0)
		;
}
