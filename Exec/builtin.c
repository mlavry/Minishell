/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:07:27 by aboutale          #+#    #+#             */
/*   Updated: 2025/05/14 20:50:43 by mlavry           ###   ########.fr       */
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
	//if (!cmd || !cmd->name)
	//	return (0);
	if (ft_strcmp(cmd->name, "echo") == 0)
		builtin_echo(data);
	else if (ft_strcmp(cmd->name, "pwd") == 0)
		builtin_pwd();
	else if (ft_strcmp(cmd->name, "env") == 0)
		builtin_env(env_list);
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


int	antislash(const char *str, int i)
{
	int	j;
	int	b_slash;

	j = 0;
	b_slash = 0;
	while (str[i] == '\\')
	{
		b_slash++;
		i++;
	}
	while (j < (b_slash / 2))
	{
		ft_putchar ('\\');
		j++;
	}
	if (b_slash % 2 == 1)
	{
		if (str[i] != '\0')
			ft_putchar(str[i++]);
	}
	else if (str[i] != '\0')
		ft_putchar(str[i++]);
	return (i);
}

void	print_antislash(const char *str)
{
	int	i;
	int	j;
	int	b_slash;

	i = 0;
	j = 0;
	while (str[i])
	{
		b_slash = 0;
		i = antislash(str,i);
	}
}


void	echo(t_env *env_list, int i, t_cmd *cmd, t_data *data)
{
	char	*value;

	if (cmd->args[i][0] == '$')
	{
		if (cmd->args[i][1] == '\0')
			printf("$");
		else if (cmd->args[i][1] == '?')
		{
			printf("%d", data->exit_code);
			if (cmd->args[i][2] != '\0')
				printf("%s", &cmd->args[i][2]);
		}
		value = getenvp(env_list, cmd->args[i] + 1);
		if (value)
			printf("%s", value);
	}
	else if (cmd->args[i][0] == '\\')
	{
		if (cmd->args[i][1] >= 'a' && cmd->args[i][1] <= 'z')
			printf("%s", &cmd->args[i][1]);
		else
			print_antislash(&cmd->args[i][1]);
	}
	else
		printf("%s", cmd->args[i]);
}


void	builtin_echo(t_data *data)
{
	int		i;
	int		j;
	int		newline;
	char	**args;
	t_cmd	*cmd;
	t_env	*env_list;

	cmd = data->cmd;
	env_list = data->env;
	i = 1;
	j = 1;
	newline = 1;
	args = cmd->args;

	while (args[i] && args[i][0] == '-' && args[i][1] == 'n')
	{
		while (args[i][j] == 'n')
		{
			j++;
			data->exit_code = 0;
		}
		if (args[i][j] != '\0')
			break ;
		newline = 0;
		i++;
	}
	while (args[i])
	{
		echo(env_list, i, cmd, data);
		if (cmd->args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
	{
		printf("\n");
		data->exit_code = 0;
	}
} 

void	builtin_exit(t_data *data)
{

	printf("exit\n");
	free_env_list(data->env);
	free_tab(data->cmd->args);
	exit(0);
}
