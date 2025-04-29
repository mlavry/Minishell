/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 21:42:28 by aboutale          #+#    #+#             */
/*   Updated: 2025/04/29 19:42:28 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_env( t_env *env_list)
{
/* 	if (!env_list)
		return ; */

	while (env_list)
	{
		if (env_list->value != NULL && env_list->value[0] != '\0')
			printf("%s=%s\n", env_list->name, env_list->value);
		env_list = env_list->next;
	}
	printf("_=/usr/bin/env\n");
}

void	emptyenv(t_env **env_list)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (*env_list == NULL)
	{
		add_env_var(env_list, "PWD", cwd);// PWD = chemin actuel
		add_env_var(env_list, "SHLVL", "1");
	}
	free(cwd);
}

void	builtin_cd(t_env **env_list, char *newpath)
{
	char	path[1024];

	if (newpath == NULL)
	{
		newpath = getenv("HOME");
		chdir("/home");
	}
	if (access(newpath, F_OK) != 0)
	{
		printf("bash: cd: %s: No such file or directory\n", newpath);
		return ;
	}
	getcwd(path, sizeof(path));
	chdir(newpath);
	updatepwd(env_list, path);
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
