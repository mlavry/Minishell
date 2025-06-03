/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:07:27 by aboutale          #+#    #+#             */
/*   Updated: 2025/06/03 20:29:03 by mlavry           ###   ########.fr       */
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

int	is_numeric(const char *str)
{
	int	i;

	i = 0;

	if (!str)
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	builtin_exit(t_data *data)
{
	char **args = data->cmd->args;

	printf("exit\n");
	if (args[1])
	{
		if (!is_numeric(args[1]))
		{
			// argument non numérique
			printf("bash: exit: %s: numeric argument required\n", args[1]);
			free_all(data, 255, true); // quitter avec code 255
		}
		else if (args[2])
		{
			// trop d'arguments
			printf("bash: exit: too many arguments\n");
			data->exit_code = 1;
			return;
		}
		else
		{
			// argument unique numérique → quitter avec ce code
			int exit_code = ft_atoi(args[1]) % 256;
			if (exit_code < 0)
				exit_code += 256;
			free_all(data, exit_code, true);
		}
	}
	else
	{
		// pas d'arguments → quitter avec le code courant
		free_all(data, data->exit_code, true);
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
