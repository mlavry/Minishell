/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:55:00 by mlavry            #+#    #+#             */
/*   Updated: 2025/06/27 00:37:07 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

bool	empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == ':' || line[i] == '.'))
	{
		i++;
		g_exit_status = 0;
	}
	if (line[0] == '|' && line[1] == '|')
	{
		printf("bash: syntax error near unexpected token `||'\n");
		g_exit_status = 2;
		return (true);
	}
	if (line[i] == '!')
	{
		i++;
		g_exit_status = 1;
	}
	if (i == (int)ft_strlen(line))
	{
		free(line);
		return (true);
	}
	return (false);
}

void	minishell_loop(t_data *data)
{
	while (1)
	{
		init_signals_prompt();
		data->line = readline("minishell$ ");
		if (!data->line)
		{
			ft_putstr_fd("exit\n", 2);
			free_all(data, g_exit_status, true);
		}
		if (empty_line(data->line))
			continue ;
		add_history(data->line);
		if (!parse_line(data))
			continue ;
		else
			executecommand(data);
		free_token(&data->token);
		free_cmd(&data->cmd);
		free(data->line);
		if (data->expand_hd)
		{
			free(data->expand_hd);
			data->expand_hd = NULL;
		}
	}
}

int	main(int argc, char *argv[], char **envp)
{
	t_data	data;

	if (!isatty(1))
		return (ft_putstr_fd("Error output is not a terminal\n", 2), 1);
	if (!isatty(0))
		return (ft_putstr_fd("Error intput is not a terminal\n", 2), 1);
	init_data(&data, argc, argv, envp);
	if (!envp || !*envp || !envp[0])
		emptyenv(&data, &data.env);
	else
		parse_env(envp, &data);
	execshell(&data, &data.env);
	minishell_loop(&data);
	free_all(&data, 0, true);
	rl_clear_history();
	return (0);
}
