/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 21:42:28 by aboutale          #+#    #+#             */
/*   Updated: 2025/05/13 22:46:39 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_env(t_data *data)
{
/* 	if (!env_list)
		return ; */

	while (data->env)
	{
		if (data->env->value != NULL && data->env->value[0] != '\0')
			printf("%s=%s\n", data->env->name, data->env->value);
		data->env = data->env->next;
	}
	printf("_=/usr/bin/env\n");
}

void	emptyenv(t_data *data)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (data->env == NULL)
	{
		add_env_var(data, "PWD", cwd);// PWD = chemin actuel
		add_env_var(data, "SHLVL", "1");
	}
	free(cwd);
}

void	builtin_cd(char *newpath, t_data *data)
{
	char	path[1024];

	if ( newpath[0] == '~')
	{
		const char *home = getenv("HOME");
   	 	if (home) 
		{
        // Crée une nouvelle chaîne en remplaçant ~ par le chemin complet
        	char *expanded_path = malloc(strlen(home) + strlen(newpath));
        	strcpy(expanded_path, home);
        	strcat(expanded_path, newpath + 1); // Ignore le ~ et concatène le reste
        	newpath = expanded_path;
    	}
	}
	if (newpath == NULL)
	{
		newpath = getenv("HOME");
		chdir("/home");
	}
	if (access(newpath, F_OK) != 0)
	{
		printf("bash: cd: %s: No such file or directory\n", newpath);
		data->exit_code = 1;
		return ;
	}
	getcwd(path, sizeof(path));
	chdir(newpath);
	updatepwd(data, path);
}

void	unset(t_env **env_list, char *name )
{
	t_env	*current;
	t_env	*previous;

	current = *env_list;
	previous = NULL;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			if (previous)
				previous->next = current->next;
			else
				*env_list = current->next;
			free(current->name);
			free(current->value);
			free(current);
			break ;
		}
		previous = current;
		current = current->next;
	}
}

void	builtin_unset(t_env **env_list, t_cmd *cmd)
{
	char	*name;
	int		i;

	if (!cmd->args || !cmd->args[1])
		return ;
	i = 1;
	while (cmd->args[i])
	{
		name = cmd->args[i];
		unset(env_list, name);
		i++;
	}
}
