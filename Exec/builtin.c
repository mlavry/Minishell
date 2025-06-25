/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:07:27 by aboutale          #+#    #+#             */
/*   Updated: 2025/06/16 23:40:26 by mlavry           ###   ########.fr       */
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
		builtin_unset(&data->env, cmd);
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

static int	validate_exit_code(t_data *data, int *exit_code)
{
	if (!is_numeric(data->cmd->args[1]))
	{
		ft_putstr_fd("exit: ", 2);
		handle_command_error(data->cmd->args[1],
			"numeric argument required\n", 2, data);
		return (0);
	}
	else if (!ft_atoi_safe(data->cmd->args[1], exit_code))
	{
		ft_putstr_fd("exit: ", 2);
		handle_command_error(data->cmd->args[1],
			"numeric argument required\n", 2, data);
		return (0);
	}
	return (1);
}

void	builtin_exit(t_data *data)
{
	int	exit_code;

	ft_putstr_fd("exit\n", 2);
	if (data->cmd->args[1])
	{
		if (!validate_exit_code(data, &exit_code))
			return ;
		else if (data->cmd->args[2])
		{
			ft_putstr_fd("exit: too many arguments\n", 2);
			g_exit_status = 1;
		}
		else
		{
			exit_code = ft_atoi(data->cmd->args[1]) % 256;
			if (exit_code < 0)
				exit_code += 256;
			free_all(data, exit_code, true);
		}
	}
	else
		free_all(data, g_exit_status, true);
}
