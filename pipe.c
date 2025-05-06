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

#include "minishell.h"

void	exec_pipe(t_cmd *cmd,t_env *env_list)
{
	int		pipe_fd[2];
	pid_t	pid;
	int	prev_fd;

	prev_fd = -1;

	while (cmd)
	{
		if (cmd->next)
			pipe(pipe_fd);
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			if (cmd->fd_in != STDIN_FILENO)
				dup2(cmd->fd_in, STDIN_FILENO);
			else if (prev_fd != -1)
				dup2(prev_fd, STDIN_FILENO);

			if (cmd->fd_out != STDOUT_FILENO)
				dup2(cmd->fd_out, STDOUT_FILENO);
			else if (cmd->next)
				dup2(pipe_fd[1], STDOUT_FILENO);

			if (prev_fd != -1)
				close(prev_fd);
			if (cmd->next)
			{
				close(pipe_fd[0]);
				close(pipe_fd[1]);
			}
			exec_extern_command(cmd->args, env_list, cmd);
		}
		prev_fd = pipe_fd[0];
		cmd = cmd->next;
	}

	while (wait(NULL) > 0)
		;

}


/* void exec_pipe(t_cmd *cmd, t_env *env_list)
{
	int fd[2];
	pid_t pid;
	t_cmd *current_cmd = cmd;

	while (current_cmd)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			if(current_cmd->fd_in != 0)
				dup2(current_cmd->fd_in, 0);
			if (current_cmd->next)
				dup2(fd[1], 1);
			close(fd[0]);
			exec_extern_command(current_cmd->args, env_list, current_cmd);
			exit(0);
		}
		else
		{
			wait(NULL);
			close(fd[1]);
			current_cmd = current_cmd->next;
		}
	}
} */