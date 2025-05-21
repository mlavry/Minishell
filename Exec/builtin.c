/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:07:27 by aboutale          #+#    #+#             */
/*   Updated: 2025/05/07 00:33:34 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	isbuiltin(t_data *data)
{
	char	*cmd;

	if (!data || !data->cmd || !data->cmd->name)
		return (0);
	cmd = data->cmd->name;
	return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "env") == 0 || ft_strcmp(cmd, "exit") == 0
		|| ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0);
}

void	exec_builtin(t_data *data)
{
	t_cmd	*cmd;
	t_env	*env_list;

	env_list = data->env;
	cmd = data->cmd;
	if (!cmd || !cmd->name)
		exit(0);
	if (ft_strcmp(cmd->name, "echo") == 0)
		builtin_echo(data);
	else if (ft_strcmp(cmd->name, "pwd") == 0)
		builtin_pwd();
	else if (ft_strcmp(cmd->name, "env") == 0)
		builtin_env(env_list, data);
	else if (ft_strcmp(cmd->name, "exit") == 0)
		builtin_exit(data);
	else if (ft_strcmp(cmd->name, "cd") == 0)
		builtin_cd(cmd->args[1], data);
	else if (ft_strcmp(cmd->name, "export") == 0)
		builtin_export(data, &env_list, cmd);
	else if (ft_strcmp(cmd->name, "unset") == 0)
		builtin_unset(&env_list, cmd);
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

void	builtin_exit(t_data *data)
{
	printf("exit\n");
	free_all(data, data->exit_code, true);
}

void	builtin_env( t_env *env_list, t_data *data)
{
	t_cmd	*cmd;

	cmd = data->cmd;
	if (cmd->args[1])
		printf("env: ‘%s’: No such file or directory\n", cmd->args[1]);

	else
	{
		while (env_list)
		{
			if (env_list->value != NULL && env_list->value[0] != '\0')
				printf("%s=%s\n", env_list->name, env_list->value);
			env_list = env_list->next;
		}
		printf("_=/usr/bin/env\n");
	}
}
