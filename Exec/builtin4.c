/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:02:27 by aboutale          #+#    #+#             */
/*   Updated: 2025/06/26 20:45:17 by mlavry           ###   ########.fr       */
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
	{
		ft_putstr_fd("env: ", 2);
		print_error(cmd->args[1], "No such file or directory\n");
	}
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

void	built_path(char *newpath, t_data *data)
{
	char	cwd[1024];

	if (!check_cd_errors(newpath))
		return ;
	if (!getcwd(cwd, sizeof(cwd)))
	{
		ft_putstr_fd("cd: error retrieving current directory\n", 2);
		if (chdir("/.") == 0)
			updatepwd(data, &data->env, "/");
		else
			g_exit_status = 1;
		return ;
	}
	if (chdir(newpath) != 0)
	{
		ft_putstr_fd("cd: ", 2);
		perror(newpath);
		g_exit_status = 1;
		return ;
	}
	updatepwd(data, &data->env, cwd);
}
