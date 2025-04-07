/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <taaikiazerolier@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:43:10 by aboutale          #+#    #+#             */
/*   Updated: 2025/04/07 21:03:16 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*getenvp(t_env *list, char *name)
{

	while (list)
	{
		if (ft_strcmp(list->name, name) == 0)
			return (list->value);
		list = list->next;

	}
	return (NULL);
}

void	add_env_var(t_env **env_list, char *name, char *value)
{
    t_env	*new_var = malloc(sizeof(t_env));
    t_env	*tmp;

	if (!new_var)
		return ;
	new_var->name = ft_strdup(name);
	new_var->value = ft_strdup(value);
	new_var->next = NULL;

	if (!*env_list)
	{
		*env_list = new_var;
		return ;
	}
	tmp = *env_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_var;
}

void parse_env(char **envp, t_data *env_list)
{
	int		i;
	char	*name;
	char	*value;
	char	*equal_pos;

	i = 0;
	while (envp[i])
	{
		equal_pos = strchr(envp[i], '=');
		if (!equal_pos)
		{
			i++;
			continue ;
		}
		name = ft_substr(envp[i], 0, equal_pos - envp[i]); // Copie avant '='
		value = ft_strdup(equal_pos + 1); // Copie après '='
		add_env_var(&env_list->env, name, value);
		free(name);
		free(value);
		i++;
	}
}




char *getpath(char **envp, char *cmd)
{
	char *path;
	char **token;
	char *full_path = NULL;
	int i = 0;
	path= getenv("PATH");
	(void)envp;

	if (cmd[0] == '/' || cmd[0] == '.')
    {
        if (access(cmd, X_OK) == 0) // Vérifie si l'exécutable existe
            return ft_strdup(cmd); // Retourne directement le chemin
        return NULL; // Le fichier n'existe pas ou n'est pas exécutable
    }
	if (!path)
		return NULL;
	token = ft_split(path, ':');
	while (token[i])
    {
        full_path = malloc(strlen(token[i]) + strlen(cmd) + 2);
        if (!full_path)
            break;
		ft_strcpy(full_path, token[i]);
		ft_strcat(full_path, "/");
		ft_strcat(full_path, cmd);

        if (access(full_path, X_OK) == 0)
        {
            int j = 0;
            while (token[j])
                free(token[j++]);
            free(token);
            return full_path;
        }

        free(full_path);
        i++;
    }
    return NULL;
}

void	exec_extern_command(char **args, t_env *env_list, char **envp)
{
	(void)env_list;
	pid_t pid= 0;
	int status;
	char *path = getpath(envp,args[0]);

	if (!path)
	{
		printf("bash : %s command not found\n", args[0]);
		return ;
	}
	pid = fork();
	if (pid == -1)
		return ;

	if (pid == 0)
	{
		execve(path, args, envp);
		exit(127);

	}
	else
		waitpid(pid, &status, 0);
}


/* void	executecommand(t_env *env_list, char *line, char **envp, t_cmd *cmd)
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
		exec_extern_command(cmd->args, env_list, envp);


	while (args[i])
		free(args[i++]);
	free(args);

} */

