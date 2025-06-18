/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:20:22 by aboutale          #+#    #+#             */
/*   Updated: 2025/06/17 23:03:28 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	setup_outandin(t_cmd *cmd, int prev_fd, int *pipe_fd)
{
		// STDIN ← prev_fd ou redirection
	 if (cmd->fd_in != STDIN_FILENO)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	else if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	// STDOUT ← redirection > result OU pipe
	if (cmd->fd_out != STDOUT_FILENO)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
	else if (cmd->next)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	} 
	// 🔒 Ferme les extrémités inutiles
	if (cmd->next)
		close(pipe_fd[0]);
 	if (cmd->next || cmd->fd_out == STDOUT_FILENO)
		close(pipe_fd[1]);
	if (prev_fd != -1)
		close(prev_fd); 
}

void	exec_command(t_cmd *cmd, t_data *data)
{
	char	*path;

	if (!cmd->args || !cmd->args[0])
		exit(0);
	if (isbuiltin(data))
	{
		exec_builtin(data);
		close_all_fd();
		exit(0);
	}
	path = getpath(cmd->args[0], data);
	if (!path)
	{
		close_all_fd();
		handle_command_error(cmd->args[0], "command not found\n", 127, data);
	}
	reset_signals_to_default();
	if (execve(path, cmd->args, convert_env(data->env)) == -1)
	{
		close_all_fd();
		perror("execve");
	}
	exit(127);
}


void	children(t_cmd *cmd, t_data *data, int prev_fd, int *pipe_fd)
{
	data->cmd = cmd;
 	if (cmd->fd_in == -1 || cmd->fd_out == -1)
		exit(1);// redirection échouée, on quitte proprement
	setup_outandin(cmd, prev_fd, pipe_fd);
	exec_command(cmd, data);
}

void	parent(t_cmd *cmd, int *pipe_fd, int *prev_fd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (cmd->next)
	{
		close(pipe_fd[1]);
		*prev_fd = pipe_fd[0];
	}
}

/* bool	is_invalid_command(char *path, char *cmd_name)
{
	if (!cmd_name || cmd_name[0] == '\0')
		return (true); // vide

	if (access(path, F_OK) != 0)
		return (true); // n'existe pas

	if (is_a_directory(path, NULL))
		return (true); // dossier

	if (access(path, X_OK) != 0)
		return (true); // pas exécutable

	return (false); // tout est ok
} */


void	exec_pipe(t_cmd *cmd, t_data *data)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		prev_fd;
	//int		status;
	char *path;

	prev_fd = -1;
	while (cmd)
	{
		if (cmd->fd_in == -1 || cmd->fd_out == -1 || !cmd->args || !cmd->args[0])
		{
    		break;
		} 
		path = getpath(cmd->args[0], data);
		if (!path)
		{
			printf("%s: command not found\n", cmd->args[0]);
			g_exit_status = 127;
			break ;
		}
	
/* 		if (!cmd->args || !cmd->args[0])
{
	g_exit_status = 127;
	fprintf(stderr, "minishell: command not found\n");
	break;
}

		if (is_invalid_command(path,cmd->args[0]))
		{
			printf("%s: command not found\n", cmd->args[0]);
    		g_exit_status = 127;
    		break;
		} 
 */
		if (cmd->next && pipe(pipe_fd) == -1)
		{
			perror("pipe");
			exit(1);
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(1);
		}
		if (pid == 0)
			children(cmd, data, prev_fd, pipe_fd);
		parent(cmd, pipe_fd, &prev_fd);
		cmd = cmd->next;
	}
/* 	while ((pid = wait(&status)) > 0)
		g_exit_status = WEXITSTATUS(status);
	close_all_fd();  */
	 while (wait(NULL) > 0)
		;
	if (prev_fd != -1)
		close(prev_fd);
}
