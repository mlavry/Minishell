/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 20:57:16 by aboutale          #+#    #+#             */
/*   Updated: 2025/04/20 20:57:17 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_extern_command(char **args, t_env *env_list, t_cmd *cmd)
{
	pid_t	pid;
	int		status;
	char	*path;

	path = getpath(args[0], cmd);
	if (!path)
	{
		printf("bash : %s command not found\n", args[0]);
		free(path);
		cmd->g_exit = 127;
		return ;
	}
	pid = fork();
	if (pid == -1)
		return (perror("fork"), cmd->g_exit = 1, free(path));
	if (pid == 0)
	{
		execve(path, args, convert_env(env_list));
		perror("execve");
		exit(127);
	}
	else
	{
		waitpid(pid, &status, 0);
		free(path);
	}
	if (WIFEXITED(status))
		cmd->g_exit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		cmd->g_exit = 128 + WTERMSIG(status);
}

void	executecommand(t_env *env_list, char *line, t_cmd *cmd)
{
	char	**args;
	int		i;

	i = 0;
	args = ft_split(line, ' ');
	if (!args[0])
	{
		free(args);
		return ;
	}
	cmd->name = args[0];
	cmd->args = args;
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	cmd->next = NULL;
	if (!isbuiltin(cmd, env_list))
		exec_extern_command(cmd->args, env_list, cmd);
	free_split(args);
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
