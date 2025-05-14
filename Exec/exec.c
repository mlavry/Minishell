/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 20:57:16 by aboutale          #+#    #+#             */
/*   Updated: 2025/05/14 19:33:51 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_extern_command(char **args, t_env *env_list, t_data *data)
{
	pid_t		pid;
	int			status;
	char		*path;
	struct stat	sb;

	path = getpath(args[0], data);
	if (!path)
	{
		printf("bash : %s: command not found\n", args[0]);
		free(path);
		data->exit_code = 127;
		return ;
	}
	if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
	{
		printf("bash: %s: Is a directory\n", args[0]);
		free(path);
		data->exit_code = 126;
		return ;
	}
	pid = fork();
	if (pid == -1)
		return (perror("fork"), data->exit_code = 1, free(path));
	if (pid == 0)
	{
	   if (data->cmd->fd_in != STDIN_FILENO)
		{
			dup2(data->cmd->fd_in, STDIN_FILENO);
			close(data->cmd->fd_in);
		}

		if (data->cmd->fd_out != STDOUT_FILENO)
		{
			dup2(data->cmd->fd_out, STDOUT_FILENO);
			close(data->cmd->fd_out);
		} 
		execve(path, args, convert_env(env_list));
		perror("execve");
		exit(127);
	}
	else
	{
		waitpid(pid, &status, 0);
		free(path);
		if (data->cmd->fd_in != STDIN_FILENO)
			close(data->cmd->fd_in);
		if (data->cmd->fd_out != STDOUT_FILENO)
			close(data->cmd->fd_out);
	}
	if (WIFEXITED(status))
		data->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		data->exit_code = 128 + WTERMSIG(status);
}

/*  utilitaire : libère puis remet à zéro le buffer commande de data */

/* static void	clear_cmd(t_data *data)
{
	if (!data || !data->cmd)
		return ;
	free_tab(data->cmd->args);   // libère le tableau argv 
	ft_bzero(data->cmd, sizeof(t_cmd));
} */

/* -------------------------------------------------------------------------- */
/*  APPEL PUBLIC : exécute la commande contenue dans data->line               */
/* -------------------------------------------------------------------------- */





void	executecommand(t_data *data)
{
	if (!data || !data->line || !data->env)
		return ;

	/* 1) Prépare le t_cmd à partir de la ligne courante ------------------- */
	//clear_cmd(data);                       /* réinitialise éventuellement   */
/* 	if (!init_cmd_from_line(data))
		return ; */

	/* 2) Si un pipe est déjà chainé (cas futur), on lancerait exec_pipe ---- */


	/* if (data->cmd->fd_in != STDIN_FILENO)
	{
		dup2(data->cmd->fd_in, STDIN_FILENO);
		close(data->cmd->fd_in);
	}

	if (data->cmd->fd_out != STDOUT_FILENO)
	{
		dup2(data->cmd->fd_out, STDOUT_FILENO);
		close(data->cmd->fd_out);
	}
 */
	if (data->cmd->next)
		exec_pipe(data->cmd, data->env, data);
	else if (isbuiltin(data))
	{
		int saved_in = dup(STDIN_FILENO);
		int saved_out = dup(STDOUT_FILENO);

		if (data->cmd->fd_in != STDIN_FILENO)
		{
			dup2(data->cmd->fd_in, STDIN_FILENO);
			close(data->cmd->fd_in);
		}
		if (data->cmd->fd_out != STDOUT_FILENO)
		{
			dup2(data->cmd->fd_out, STDOUT_FILENO);
			close(data->cmd->fd_out);
		}

		exec_builtin(data);

		dup2(saved_in, STDIN_FILENO);
		dup2(saved_out, STDOUT_FILENO);
		close(saved_in);
		close(saved_out);
	}
	else
	{
		/* 3) Built‑in sinon programme externe ----------------------------- */
		//if (!isbuiltin(data))
			exec_extern_command(data->cmd->args, data->env, data);
			if (data->cmd->fd_in != STDIN_FILENO)
				close(data->cmd->fd_in);
			if (data->cmd->fd_out != STDOUT_FILENO)
				close(data->cmd->fd_out);
	}

	/* 4) Nettoyage local : les fd (si redirs) seraient fermés ailleurs ----- */
	/*    On ne libère PAS data->cmd lui‑même : il est conservé pour réutili‑
	      sation. Seul le tableau args est libéré juste avant le prochain tour */
}

t_env	*find_env_var(t_env *env_list, char *name)
{
	while (env_list != NULL)
	{
		if (ft_strcmp(env_list->name, name) == 0)
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}


/* void cleanup_env(t_env **env_list)
{
    t_env *current;
    t_env *temp;

    current = *env_list;
    while (current)
    {
        // Libérer la mémoire de la chaîne de chaque variable d'environnement
        free(current->value);
        
        // Passer à l'élément suivant
        temp = current;
        current = current->next;

        // Libérer la structure elle-même si nécessaire
        free(temp);
    }
} */

/* void free_env_var(t_env *var)
{
    if (var)
    {
        if (var->name)
            free(var->name);
        if (var->value)
            free(var->value);
        free(var);
    }
} */

void	execshell( t_env **env_list)
{
	t_env	*shlvl;
	int		level;
	char	*new_val ;

	shlvl = find_env_var(*env_list, "SHLVL");
	if (!shlvl)
		return ;
	if (shlvl)
	{
		level = ft_atoi(shlvl->value);
		level++;
		new_val = ft_itoa(level);
		if (new_val)
		{
			free(shlvl->value);
			shlvl->value = new_val;
		}
	}
}
