/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 21:00:48 by aboutale          #+#    #+#             */
/*   Updated: 2025/06/26 21:00:51 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_child_status(int status, pid_t pid, pid_t last, bool *print)
{
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT
		&& !*print && pid != last)
	{
		write(STDOUT_FILENO, "\n", 1);
		*print = true;
	}
	if (pid == last)
	{
		if (!*print)
			handle_status_and_print(status);
		else
			g_exit_status = 130;
	}
}

void	wait_process(pid_t last_pid)
{
	int		status;
	pid_t	pid_wait;
	bool	printed;

	printed = false;
	ignore_sigint();
	while (1)
	{
		pid_wait = wait(&status);
		if (pid_wait <= 0)
			break ;
		handle_child_status(status, pid_wait, last_pid, &printed);
	}
}

int	handle_one_pipe(t_cmd *current_cmd, int *prev_fd, int *pipe_fd, pid_t *pid)
{
	if (current_cmd->next)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe");
			if (*prev_fd != -1)
				close(*prev_fd);
			return (0);
		}
	}
	*pid = fork();
	if (*pid == -1)
	{
		perror("fork");
		if (*prev_fd != -1)
			close(*prev_fd);
		if (current_cmd->next)
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
		}
		return (0);
	}
	return (1);
}

static void	child_process(t_cmd *cmd, t_data *data, int prev_fd, int *pipe_fd)
{
	setup_outandin(cmd, prev_fd, pipe_fd);
	exec_command(cmd, data);
}

void	exec_pipe(t_cmd *cmd, t_data *data)
{
	int		pipe_fd[2];
	pid_t	pid;
	pid_t	last_pid;
	int		prev_fd;
	t_cmd	*current_cmd;

	last_pid = -1;
	prev_fd = -1;
	current_cmd = cmd;
	while (current_cmd)
	{
		if (!handle_one_pipe(current_cmd, &prev_fd, pipe_fd, &pid))
			return ;
		if (pid == 0)
			child_process(current_cmd, data, prev_fd, pipe_fd);
		else
		{
			if (current_cmd->next == NULL)
				last_pid = pid;
			parent(current_cmd, &prev_fd, pipe_fd);
		}
		current_cmd = current_cmd->next;
	}
	wait_process(last_pid);
}
