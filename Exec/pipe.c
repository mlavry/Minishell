/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:20:22 by aboutale          #+#    #+#             */
/*   Updated: 2025/04/22 16:20:24 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	input(t_data *data, int prev_fd)
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
}

void output(t_data *data, int pipe_fd[2])
{
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

			input(data, prev_fd);
			output(data, pipe_fd);
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
				exec_extern_command(data->cmd->args, data->env,  data);
			exit(EXIT_SUCCESS); // Important si builtin ne fait pas exit
}

void	exec_pipe(t_cmd *cmd, t_data *data)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		prev_fd = -1;

	while (cmd)
	{
		data->cmd = cmd;
		if (cmd->next && pipe(pipe_fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}

		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}

		if (pid == 0)
			childprocess(data, prev_fd, pipe_fd);
		else
		{
			if (prev_fd != -1)
				close(prev_fd);
			if (cmd->next)
				close(pipe_fd[1]); // le parent ne garde que la lecture
			prev_fd = (cmd->next) ? pipe_fd[0] : -1;
			cmd = cmd->next;
		}
	}
	while (wait(NULL) > 0)
		;
}
