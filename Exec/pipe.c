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

	 if (cmd->fd_in != STDIN_FILENO)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	else if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		//close(prev_fd);
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
		//close(pipe_fd[1]);
	} 
	// 🔒 Ferme les extrémités inutiles
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

void	exec_command(t_cmd *cmd, t_data *data)
{
	char	*path;
    char    **envi;
     t_cmd   *original_cmd_head = data->cmd;

	if (!cmd || !cmd->args || !cmd->args[0])
		exit(0);
    data->cmd = cmd;   
	if (isbuiltin(data))
	{
		exec_builtin(data);
        data->cmd = original_cmd_head; 
        free_all(data,g_exit_status, true);
		//close_all_fd();
		exit(0);
	}
    data->cmd = original_cmd_head;
	path = getpath(cmd->args[0], data);
	if (!path)
	{
		//close_all_fd();
		handle_command_error(cmd->args[0], "command not found\n", 127, data);
       // free(path);
	}
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
	//dprintf(2, "EXECUTING CMD: %s\n", cmd->args[0]);
	//exit(127);
}



void children(t_cmd *cmd, t_data *data, int prev_fd, int *pipe_fd)
{

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
        printf("salu\n")   ; 
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
        free_all(data, 0, true);
        //exit(1);
    }

   // data->cmd = cmd;

    setup_outandin(cmd, prev_fd, pipe_fd);
    exec_command(cmd, data);
    free_all(data, g_exit_status, true);
}


/* void	children(t_cmd *cmd, t_data *data, int prev_fd, int *pipe_fd)
{
	 if (!cmd || !cmd->args || !cmd->args[0])
	 {

		if (prev_fd != -1)
			close(prev_fd);
		if (pipe_fd)
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
		}
		if (cmd && cmd->fd_in > 2)
			close(cmd->fd_in);
		if (cmd && cmd->fd_out > 2)
			close(cmd->fd_out);
		exit(0); // Ne rien faire si la commande est vide
	}
	data->cmd = cmd;

	setup_outandin(cmd, prev_fd, pipe_fd);
	if (cmd->fd_in == -1 || cmd->fd_out == -1)
		exit(1);// redirection échouée, on quitte proprement
	//dprintf(2, "CHILD: cmd = %s\n", cmd->args ? cmd->args[0] : "NULL");	
	exec_command(cmd, data);
} */

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
        if (pipe_fd[0] != -1)
        {
            fprintf(stderr, "PARENT: closing pipe_fd[0] %d (last command)\n", pipe_fd[0]);
            close(pipe_fd[0]); // <-- cette ligne manquait !
        }
        if (pipe_fd[1] != -1)
        {
            fprintf(stderr, "PARENT: closing pipe_fd[1] %d (last command)\n", pipe_fd[1]);
            close(pipe_fd[1]);
        }
        *prev_fd = -1;
	}
}

/* void parent(t_cmd *cmd, int *pipe_fd, int *prev_fd)
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
} */

/* 
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


void exec_pipe(t_cmd *cmd, t_data *data)
{
    int   pipe_fd[2];
    pid_t pid;
    pid_t last_pid = -1;
    int   prev_fd = -1;
    int   status = 0;
    t_cmd *current_cmd = cmd;

    while (current_cmd)
    {
        // On crée un pipe si la commande actuelle n'est pas la dernière
        if (current_cmd->next)
        {
            if (pipe(pipe_fd) == -1)
            {
                perror("pipe");
                // Nettoyage avant de quitter
                if (prev_fd != -1) close(prev_fd);
                return;
            }
        }

        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            // Nettoyage avant de quitter
            if (prev_fd != -1) close(prev_fd);
            if (current_cmd->next) { close(pipe_fd[0]); close(pipe_fd[1]); }
            return;
        }

        if (pid == 0) // --- Processus Enfant ---
        {
            // setup_outandin se charge de dup2 et de fermer les FDs dans l'enfant.
            // Votre logique dans setup_outandin semble déjà correcte.
            setup_outandin(current_cmd, prev_fd, pipe_fd);
            
            // exec_command va exécuter la commande et appeler exit().
            exec_command(current_cmd, data);
        }
        
        // --- Processus Parent (dans la boucle) ---
        
        // 1. Fermer le FD d'entrée qui vient du pipe précédent.
        // L'enfant en a hérité, le parent n'en a plus besoin.
        if (prev_fd != -1)
            close(prev_fd);

        // 2. Préparer le `prev_fd` pour la prochaine itération de la boucle.
        if (current_cmd->next)
        {
            close(pipe_fd[1]); // Le parent n'écrit JAMAIS dans le pipe.
            prev_fd = pipe_fd[0]; // On garde l'extrémité de lecture pour le prochain enfant.
        }

        // 3. *** LA CORRECTION LA PLUS IMPORTANTE EST ICI ***
        // Le parent DOIT fermer SA copie des descripteurs de fichiers de redirection
        // pour la commande qu'il vient de lancer. C'est ça qui corrige la fuite.
        if (current_cmd->fd_in != STDIN_FILENO)
            close(current_cmd->fd_in);
        if (current_cmd->fd_out != STDOUT_FILENO)
            close(current_cmd->fd_out);
        // Note : si vous utilisez `heredoc_file`, le fd correspondant est dans `fd_in`.
        // Cette correction gère donc aussi les heredocs.

        // On garde le PID de la dernière commande pour récupérer son statut
        if (current_cmd->next == NULL)
            last_pid = pid;

        current_cmd = current_cmd->next;
    }

    // --- Processus Parent (après la boucle) ---
    // Attendre la fin de TOUS les processus enfants.
    ignore_sigint();
    int pid_wait;
	int last_status;

    while ((pid_wait = wait(&status)) > 0)
    {
        if (pid_wait == last_pid)
		{
			// On stocke le statut de la dernière commande mais on ne l'évalue pas encore
			last_status = status;
		}
    }
    
	// Une fois que tous les enfants sont terminés, on traite le statut de la dernière commande
	if (last_pid != -1)
		handle_status_and_print(last_status);

    // close_all_fd() est une sécurité, mais la gestion ci-dessus est plus propre.
    // Vous pouvez la garder si vous le souhaitez.
}


// void	exec_pipe(t_cmd *cmd, t_data *data)
// {
//     int		pipe_fd[2];
//     pid_t	pid;
//     pid_t	last_pid;
//     int		prev_fd;
//     int		status;
//     //t_cmd *head;

//     //head = cmd;

//     prev_fd = -1;
//     while (cmd)
//     {
//         if (cmd->next)
//             pipe(pipe_fd);
		
//         pid = fork();
//         if (pid == -1)
//         {
//             perror("fork");
//             exit(1);
//         }

//         if (pid == 0)
//             children(cmd, data, prev_fd, pipe_fd);
        
//         if (cmd->next == NULL)
//             last_pid = pid;

//         parent(cmd, pipe_fd, &prev_fd);
//         //cmd = cmd->next;
//         cmd = cmd->next;
//     }

//     ignore_sigint();
//     bool sigint_printed = false;
//     while ((pid = wait(&status)) > 0)
//     {
//         if (WIFSIGNALED(status))
//         {
//             int sig = WTERMSIG(status);
//             if (sig == SIGINT && !sigint_printed && pid != last_pid)
//             {
//                 write(STDOUT_FILENO, "\n", 1);
//                 sigint_printed = true;
//             }
//         }
//         if (pid == last_pid && !sigint_printed)
//             handle_status_and_print(status);
//         else if (pid == last_pid && sigint_printed)
//             g_exit_status = 130;
//     }

//     close_all_fd();
// } 



