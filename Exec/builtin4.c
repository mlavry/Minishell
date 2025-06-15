/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:02:27 by aboutale          #+#    #+#             */
/*   Updated: 2025/06/12 18:02:30 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	builtin_env( t_env *env_list, t_data *data)
{
	t_cmd	*cmd;

	cmd = data->cmd;
	if (cmd->args[1] && ft_strcmp(cmd->args[1], "env") != 0)
		printf("env: ‘%s’: No such file or directory\n", cmd->args[1]);
	else
	{
		while (env_list)
		{
			if (env_list->value != NULL)
				printf("%s=%s\n", env_list->name, env_list->value);
			env_list = env_list->next;
		}
		printf("_=/usr/bin/env\n");
	}
}

void	emptyenv(t_data *data, t_env **env_list)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		malloc_failed(data);
	if (*env_list == NULL)
	{
		add_env_var(data, env_list, "PWD", cwd);
		add_env_var(data, env_list, "PATH", "/usr/bin:/bin");
	}
	free(cwd);
}

void	builtin_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		printf("%s\n", cwd);
		free(cwd);
	}
	else
		perror("cwd");
}
