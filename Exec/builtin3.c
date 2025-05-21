/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 22:18:28 by aboutale          #+#    #+#             */
/*   Updated: 2025/05/19 22:18:31 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		i = antislash(str, i);
	}
}

void	echo(t_env *env_list, int i, t_cmd *cmd, t_data *data)
{
	(void)data;
	(void)env_list;
	//char	*value;
	/* if (cmd->args[i][0] == '$')
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
	} */
	if (cmd->args[i][0] == '\\')
	{
		if (cmd->args[i][1] >= 'a' && cmd->args[i][1] <= 'z')
			printf("%s", &cmd->args[i][1]);
		else
			print_antislash(&cmd->args[i][1]);
	}
	else
		printf("%s", cmd->args[i]);
}

int	check_newline(t_data *data, char **args, int *i)
{
	int	j;
	int	newline ;

	newline = 1;
	while (args[*i] && args[*i][0] == '-' && args[*i][1] == 'n')
	{
		j = 1;
		while (args[*i][j] == 'n')
		{
			j++;
			data->exit_code = 0;
		}
		if (args[*i][j] != '\0')
			break ;
		newline = 0;
		(*i)++;
	}
	return (newline);
}

void	builtin_echo(t_data *data)
{
	int		i;
	int		newline;
	char	**args;
	t_cmd	*cmd;
	t_env	*env_list;

	cmd = data->cmd;
	env_list = data->env;
	i = 1;
	args = cmd->args;
	newline = check_newline(data, args, &i);
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
