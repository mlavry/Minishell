/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:20:22 by aboutale          #+#    #+#             */
/*   Updated: 2025/06/25 21:12:27 by mlavry           ###   ########.fr       */
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
	if(data->cmd && data->cmd->args && data->cmd->args[0]
		&& ft_strcmp(data->cmd->args[0], "exit") == 0)
	{
		// On est dans un pipe, donc on n'exécute pas "exit"
		data->cmd = original_cmd_head;
		free_all(data, g_exit_status, true);
		exit(0); // quitter proprement le processus fils sans quitter le shell
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
	{
		builtin_in_pipe(data, original_cmd_head);
		/* exec_builtin(data);
		data->cmd = original_cmd_head;
		free_all(data, g_exit_status, true);
		exit(0); */
	}
	data->cmd = original_cmd_head;
	path = getpath(cmd->args[0], data);
	if (!path)
		handle_command_error(cmd->args[0], "command not found\n", 127, data);
	reset_signals_to_default();
	envi = convert_env(data->env);
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

void    wait_process(pid_t last_pid)
{
    int     status;
    pid_t   pid_wait;
    int     sig;
    bool    sigint_printed;

    sigint_printed = false;
    ignore_sigint();
    while (1)
    {
        pid_wait = wait(&status);
        if (pid_wait <= 0)
            break ;
        if (WIFSIGNALED(status))
        {
            sig = WTERMSIG(status);
            if (sig == SIGINT && !sigint_printed && pid_wait != last_pid)
            {
                write(STDOUT_FILENO, "\n", 1);
                sigint_printed = true;
            }
        }
        if (pid_wait == last_pid && !sigint_printed)
            handle_status_and_print(status);
        else if (pid_wait == last_pid && sigint_printed)
            g_exit_status = 130;
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
		{
			setup_outandin(current_cmd, prev_fd, pipe_fd);
			exec_command(current_cmd, data);
		}
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
