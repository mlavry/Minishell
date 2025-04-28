/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:07:27 by aboutale          #+#    #+#             */
/*   Updated: 2025/04/28 17:49:48 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	isbuiltin(t_cmd *cmd, t_env *env_list, char **args)
{
	g_exit = 0;
	if (!cmd || !cmd->name)
		return (0);
	if (ft_strcmp(cmd->name, "echo") == 0)
		builtin_echo(cmd, env_list);
	else if (ft_strcmp(cmd->name, "pwd") == 0)
		builtin_pwd(cmd);
	else if (ft_strcmp(cmd->name, "env") == 0)
		builtin_env(env_list);
	else if (ft_strcmp(cmd->name, "exit") == 0)
		builtin_exit(cmd);
	else if (ft_strcmp(cmd->name, "cd") == 0)
		builtin_cd(&env_list, cmd->args[1]);
	else if (ft_strcmp(cmd->name, "export") == 0)
		builtin_export(&env_list, args);
	else if (ft_strcmp(cmd->name, "unset") == 0)
		builtin_unset(&env_list, args);
	else
		return (0);
	return (1);
}

void	builtin_pwd(t_cmd *cmd)
{
	char	*cwd;

	(void)cmd;
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		printf("%s\n", cwd);
		free(cwd);
	}
	else
		perror("cwd");
}

void	echo(t_env *env_list, int i, t_cmd *cmd)
{
	char	*value;

	if (cmd->args[i][0] == '$')
	{
		value = getenvp(env_list, cmd->args[i] + 1);
		if (value)
			printf("%s", value);
	}
	else
		printf("%s", cmd->args[i]);
	if (cmd->args[i + 1])
		printf(" ");
}

void	builtin_echo(t_cmd *cmd, t_env *env_list)
{
	int		i;
	int		j;
	int		newline;
	char	**args;

	i = 1;
	j = 1;
	newline = 1;
	args = cmd->args;
	while (args[i] && args[i][0] == '-' && args[i][1] == 'n')
	{
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] != '\0')
			break ;
		newline = 0;
		i++;
	}
	while (args[i])
	{
		echo(env_list, i, cmd);
		i++;
	}
	if (newline)
		printf("\n");
}

void	builtin_exit(t_cmd *cmd)
{
	(void)cmd;
	printf("exit\n");
	exit(0);
}
