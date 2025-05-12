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

/* void	exec_pipe(t_cmd *cmd,t_env *env_list)
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
		if (prev_fd != -1)
			close(prev_fd);
		if (cmd->next)
			close(pipe_fd[1]);

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
			if (!isbuiltin(cmd, env_list))
				exec_extern_command(cmd->args, env_list, cmd);

			//exec_extern_command(cmd->args, env_list, cmd);
		}
		prev_fd = pipe_fd[0];
		cmd = cmd->next;
	}
	if (prev_fd != -1)
	close(prev_fd);


	while (wait(NULL) > 0)
		;

}  */



/* void childprocess(t_data *data, int prev_fd, int pipe_fd[2], t_env *env_list)
{

			if (prev_fd != -1)
				dup2(prev_fd, STDIN_FILENO);
			else if (data->cmd->fd_in != STDIN_FILENO)
			{
				dup2(data->cmd->fd_in, STDIN_FILENO);
				close(data->cmd->fd_in);
			}

			// Redirection sortie
			if (data->cmd->fd_out != STDOUT_FILENO)
			{
	
    			dup2(data->cmd->fd_out, STDOUT_FILENO);  // Redirection fichier
				close(data->cmd->fd_out);
			}
			else if (data->cmd->next)
    			dup2(pipe_fd[1], STDOUT_FILENO);  // Sinon, pipe

		 	if (cmd->next)
				dup2(pipe_fd[1], STDOUT_FILENO);
			else if (cmd->fd_out != STDOUT_FILENO)
				dup2(cmd->fd_out, STDOUT_FILENO); 

			// Fermeture des fds inutiles
			if (prev_fd != -1)
				close(prev_fd);
			if (data->cmd->next)
			{
				close(pipe_fd[0]);
				close(pipe_fd[1]);
			}

			if (!isbuiltin(data->cmd, env_list, data))
				exec_extern_command(data->cmd->args, env_list, data->cmd, data);
			exit(EXIT_SUCCESS); // Important si builtin ne fait pas exit

} */


void	exec_pipe(t_cmd *cmd, t_env *env_list, t_data *data)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		prev_fd = -1;

	while (cmd)
	{
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

		if (pid == 0) // === CHILD PROCESS ===
		{
			// Redirection entrée
			if (prev_fd != -1)
				dup2(prev_fd, STDIN_FILENO);
			else if (cmd->fd_in != STDIN_FILENO)
			{
				dup2(cmd->fd_in, STDIN_FILENO);
				close(cmd->fd_in);
			}

			// Redirection sortie
			if (cmd->fd_out != STDOUT_FILENO)
			{
	
    			dup2(cmd->fd_out, STDOUT_FILENO);  // Redirection fichier
				close(cmd->fd_out);
			}
			else if (cmd->next)
    			dup2(pipe_fd[1], STDOUT_FILENO);  // Sinon, pipe

		/* 	if (cmd->next)
				dup2(pipe_fd[1], STDOUT_FILENO);
			else if (cmd->fd_out != STDOUT_FILENO)
				dup2(cmd->fd_out, STDOUT_FILENO); */

			// Fermeture des fds inutiles
			if (prev_fd != -1)
				close(prev_fd);
			if (cmd->next)
			{
				close(pipe_fd[0]);
				close(pipe_fd[1]);
			}

			if (!isbuiltin(data))
				exec_extern_command(cmd->args, env_list,  data);
			exit(EXIT_SUCCESS); // Important si builtin ne fait pas exit
		}
		else // === PARENT PROCESS ===
		{
			if (prev_fd != -1)
				close(prev_fd);
			if (cmd->next)
				close(pipe_fd[1]); // le parent ne garde que la lecture
			prev_fd = (cmd->next) ? pipe_fd[0] : -1;
			cmd = cmd->next;
		}
	}

	// Attend tous les enfants
	while (wait(NULL) > 0)
		;
}
