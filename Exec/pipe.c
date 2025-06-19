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

/* void	setup_outandin(t_cmd *cmd, int prev_fd, int *pipe_fd)
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
}  */

void setup_outandin(t_cmd *cmd, int prev_fd, int *pipe_fd)
{
    // STDIN
    if (cmd->fd_in != STDIN_FILENO)  // redirection input
    {
        dup2(cmd->fd_in, STDIN_FILENO);
        close(cmd->fd_in);
    }
    else if (prev_fd != -1)  // sinon, lecture depuis pipe précédent
    {
        dup2(prev_fd, STDIN_FILENO);
        close(prev_fd);
    }

    // STDOUT
    if (cmd->fd_out != STDOUT_FILENO)  // redirection output
    {
        dup2(cmd->fd_out, STDOUT_FILENO);
        close(cmd->fd_out);
        // IMPORTANT : si redirigé vers fichier, on ne touche pas au pipe !
        // On ferme pipe_fd si créé, sinon le pipe pourrait traîner
        if (cmd->next)
        {
            close(pipe_fd[0]);
            close(pipe_fd[1]);
        }
    }
    else if (cmd->next)  // Pas de redirection, y a un pipe -> écrire dans pipe
    {
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);
        close(pipe_fd[0]);
    }
    else  // dernier cmd sans redirection ni pipe
    {
        if (cmd->next == NULL)
        {
            if (pipe_fd[0] != -1) close(pipe_fd[0]);
            if (pipe_fd[1] != -1) close(pipe_fd[1]);
        }
    }
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

	setup_outandin(cmd, prev_fd, pipe_fd);
	if (cmd->fd_in == -1 || cmd->fd_out == -1)
		exit(1);// redirection échouée, on quitte proprement
	exec_command(cmd, data);
}

/* 
void	children(t_cmd *cmd, t_data *data, int prev_fd, int *pipe_fd)
{
	if (!cmd->args || !cmd->args[0])
        exit(0); // juste redirection, pas de commande à exécuter
	data->cmd = cmd;
 	if (cmd->fd_in == -1 || cmd->fd_out == -1)
		exit(1);// redirection échouée, on quitte proprement
	setup_outandin(cmd, prev_fd, pipe_fd);

	exec_command(cmd, data);
} */

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


bool	has_real_command(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->args && cmd->args[0])
			return true;
		cmd = cmd->next;
	}
	return false;
}

bool	is_empty_cmd(t_cmd *cmd)
{
	return (!cmd || !cmd->args || !cmd->args[0]);
}


void	exec_pipe(t_cmd *cmd, t_data *data)
{
	int		pipe_fd[2];
	pid_t	pid;
	pid_t	last_pid;
	int		prev_fd;
	int		status;
	//char *path;

	prev_fd = -1;
	while (cmd)
	{
		
// 		/* if (has_real_command(cmd->next) && pipe(pipe_fd) == -1)
// 		{
// 				perror("pipe");
// 			exit(1);

// 		} */

// 		/* 
// 		bool next_cmd_valid = cmd->next && cmd->next->args && cmd->next->args[0];
// 		if (next_cmd_valid && pipe(pipe_fd) == -1)
// 		{
// 			perror("pipe");
// 			exit(1);
// 		} */
// 		//bool is_empty_cmd = (!cmd->args || !cmd->args[0]);
// 	//bool is_invalid = false;


// /* 	if (is_empty_cmd)
// 	{
// 	// Si on a une redirection de sortie, elle sera déjà gérée dans le parsing
// 		 if (cmd->fd_out != STDOUT_FILENO)
//             close(cmd->fd_out); 
// 		cmd = cmd->next;
// 		continue;
// 	} */

// 	/* if (!is_empty_cmd)
// 	{
		
// 		path = getpath(cmd->args[0], data);
// 		if (!path)
// 		{
// 			fprintf(stderr, "minishell: %s: command not found\n", cmd->args[0]);
// 			g_exit_status = 127;
// 			is_invalid = true;
// 		}
// 	} */

// /*  		if (cmd->fd_in == -1 || cmd->fd_out == -1 || !cmd->args || !cmd->args[0])
// 		{
//     		break;
// 		} 
// 		path = getpath(cmd->args[0], data);
// 		if (!path)
// 		{
// 			printf("%s: command not found\n", cmd->args[0]);
// 			g_exit_status = 127;
// 			break ;
// 		}   */
	
// /* 		if (!cmd->args || !cmd->args[0])
// {
// 	g_exit_status = 127;
// 	fprintf(stderr, "minishell: command not found\n");
// 	break;
// }

// 		if (is_invalid_command(path,cmd->args[0]))
// 		{
// 			printf("%s: command not found\n", cmd->args[0]);
//     		g_exit_status = 127;
//     		break;
// 		} 
//  */
// 		if ((!cmd->args || !cmd->args[0]))
// 		{
//     // On crée un fichier vide si redirection de sortie
//    			 if (cmd->fd_out != STDOUT_FILENO)
//     		{
//        	 		write(cmd->fd_out, "", 0);
//         		close(cmd->fd_out);
//         		cmd->fd_out = STDOUT_FILENO;
//     		}

//     // Si une redirection d'entrée avait été ouverte, on la ferme
//     		if (cmd->fd_in != STDIN_FILENO)
//     		{
//        	 		close(cmd->fd_in);
//         		cmd->fd_in = STDIN_FILENO;
//     		}
// 			if (has_real_command(cmd->next))
// 			{
// 				close(pipe_fd[0]);
// 				close(pipe_fd[1]);
// 			}

//     		// Et surtout : on NE FORKE PAS
//     		cmd = cmd->next;
//     		continue;
// 		}

		if ((!cmd->args || !cmd->args[0]))
		{

			if (cmd->fd_in != STDIN_FILENO)
			{
    // Ferme fd_in, pour qu’il ne lise pas le pipe précédent
   				 close(cmd->fd_in);
    			cmd->fd_in = STDIN_FILENO;
			}


		}

		bool next_cmd_valid = cmd->next && !is_empty_cmd(cmd->next);
		if (next_cmd_valid && pipe(pipe_fd) == -1)
		{
			perror("pipe");
			exit(1);
		}

		if (is_empty_cmd(cmd))
		{
			// Crée un fichier vide si redirection de sortie
			if (cmd->fd_out != STDOUT_FILENO)
			{
				write(cmd->fd_out, "", 0);
				close(cmd->fd_out);
				cmd->fd_out = STDOUT_FILENO;
			}

			if (cmd->fd_in != STDIN_FILENO)
			{
				close(cmd->fd_in);
				cmd->fd_in = STDIN_FILENO;
			}

			// 🔥 Fermer le pipe inutilement ouvert pour cette commande vide
			if (next_cmd_valid)
			{
				close(pipe_fd[0]);
				close(pipe_fd[1]);
			}

			cmd = cmd->next->next;
			continue;
		}


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
	//close_all_fd();
/* 	while ((pid = wait(&status)) > 0)
		g_exit_status = WEXITSTATUS(status);
	close_all_fd();  */
	  while (wait(NULL) > 0)
		;
	if (prev_fd != -1)
		close(prev_fd); 
}
