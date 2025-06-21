/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:20:22 by aboutale          #+#    #+#             */
/*   Updated: 2025/06/19 02:31:50 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	setup_outandin(t_cmd *cmd, int prev_fd, int *pipe_fd)
{
	 signal(SIGPIPE, SIG_IGN);
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
	if (cmd->next && pipe_fd[0] != -1)
		close(pipe_fd[0]);
 /* 	if (cmd->next || cmd->fd_out == STDOUT_FILENO)
		close(pipe_fd[1]); */
	if (prev_fd != -1)
		close(prev_fd); 
} 

bool	is_empty_cmd(t_cmd *cmd)
{
	return (!cmd || !cmd->args || !cmd->args[0]);
}


void	exec_command(t_cmd *cmd, t_data *data)
{
	char	*path;
    char **envi;

	if (!cmd || !cmd->args || !cmd->args[0])
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
    envi = convert_env(data->env);
	if (execve(path, cmd->args, envi) == -1)
	{
		close_all_fd();
        free_tab(envi);
		perror("execve");
        exit(127);
	}
	dprintf(2, "EXECUTING CMD: %s\n", cmd->args[0]);
	exit(127);
}

void children(t_cmd *cmd, t_data *data, int prev_fd, int *pipe_fd)
{
    signal(SIGPIPE, SIG_IGN);
    if (is_empty_cmd(cmd))
    {
        if (prev_fd != -1)
            close(prev_fd);
        if (pipe_fd)
        {
            if (pipe_fd[0] != -1) close(pipe_fd[0]);
            if (pipe_fd[1] != -1) close(pipe_fd[1]);
        }
        if (cmd && cmd->fd_in > 2)
            close(cmd->fd_in);
        if (cmd && cmd->fd_out > 2)
            close(cmd->fd_out);
        exit(0);
    }

    if (cmd->fd_in == -1 || cmd->fd_out == -1)
    {
        if (prev_fd != -1)
            close(prev_fd);
        if (pipe_fd)
        {
            if (pipe_fd[0] != -1) close(pipe_fd[0]);
            if (pipe_fd[1] != -1) close(pipe_fd[1]);
        }
        exit(1);
    }

    data->cmd = cmd;
    setup_outandin(cmd, prev_fd, pipe_fd);
     if (cmd->heredoc_file)
    {
        unlink(cmd->heredoc_file); // Supprime le fichier immédiatement
        free(cmd->heredoc_file);
        cmd->heredoc_file = NULL;
    }
      if (cmd->fd_in != STDIN_FILENO && cmd->fd_in != -1)
        close(cmd->fd_in);
    exec_command(cmd, data);
} 


/* 
void parent(t_cmd *cmd, int *pipe_fd, int *prev_fd)
{
    if (*prev_fd != -1)
    {
        fprintf(stderr, "PARENT: closing prev_fd %d\n", *prev_fd);
        close(*prev_fd);
    }
    if (cmd->next && pipe_fd[1] != -1)
    {
        fprintf(stderr, "PARENT: closing pipe_fd[1] %d\n", pipe_fd[1]);
        close(pipe_fd[1]);
        *prev_fd = pipe_fd[0];
    }
    else
    {
        *prev_fd = -1;
	}
} */
/* 
void parent(t_cmd *cmd, int *pipe_fd, int *prev_fd)
{
    fprintf(stderr, "PARENT: closing prev_fd %d\n", *prev_fd);
    if (*prev_fd != -1)
        close(*prev_fd);
    if (cmd->next)
    {
        fprintf(stderr, "PARENT: closing pipe_fd[1] %d\n", pipe_fd[1]);
        close(pipe_fd[1]);
        *prev_fd = pipe_fd[0];
    }
}  */


void	parent(t_cmd *cmd, int *pipe_fd, int *prev_fd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (cmd->next)
	{
		close(pipe_fd[1]);
		*prev_fd = pipe_fd[0];
	}
 	else
	{
		// Pas de commande suivante ou elle est vide
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		*prev_fd = -1;
	}
	dprintf(2, "PARENT: closing pipe_fd: %d %d\n", pipe_fd[0], pipe_fd[1]);

} 



void	close_all_fds_after_exec(t_cmd *cmd)
{
    while (cmd)
    {
        if (cmd->fd_in != STDIN_FILENO)
            close(cmd->fd_in);
        if (cmd->fd_out != STDOUT_FILENO && cmd->fd_out != -1)
            close(cmd->fd_out);

        // Supprime le fichier heredoc s'il existe
        if (cmd->heredoc_file)
        {
            unlink(cmd->heredoc_file);
            free(cmd->heredoc_file);
            cmd->heredoc_file = NULL;
        }
        cmd = cmd->next;
    }
}


void	exec_pipe(t_cmd *cmd, t_data *data)
{
    int		pipe_fd[2];
    pid_t	pid;
    pid_t	last_pid;
    int		prev_fd;
    int		status;
    t_cmd	*head; 

    head =cmd;
    prev_fd = -1;
    signal(SIGPIPE, SIG_IGN);
    while (cmd)
    {
        if (cmd->next)
            pipe(pipe_fd);
		
        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(1);
        }

        if (pid == 0)
            children(cmd, data, prev_fd, pipe_fd);
        
        if (cmd->next == NULL)
            last_pid = pid;

        parent(cmd, pipe_fd, &prev_fd);
        cmd = cmd->next;
    }

    ignore_sigint();
    bool sigint_printed = false;
    while ((pid = wait(&status)) > 0)
    {
        if (WIFSIGNALED(status))
        {
            int sig = WTERMSIG(status);
            if (sig == SIGINT && !sigint_printed && pid != last_pid)
            {
                write(STDOUT_FILENO, "\n", 1);
                sigint_printed = true;
            }
        }
        if (pid == last_pid && !sigint_printed)
            handle_status_and_print(status);
        else if (pid == last_pid && sigint_printed)
            g_exit_status = 130;
    }
     close_all_fds_after_exec(head);
 /*    while ((pid = wait(&status)) > 0)
        g_exit_status = WEXITSTATUS(status);
    close_all_fd(); */
}