/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:55:00 by mlavry            #+#    #+#             */
/*   Updated: 2025/06/19 17:17:15 by mlavry           ###   ########.fr       */
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
	if (line[0] == '|')
	{
		printf("bash: syntax error near unexpected token `|'\n");
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

void	exit_minishell(t_data *data)
{
	ft_putstr_fd("exit\n", 2);
	free_token(&data->token);
	free_cmd(&data->cmd);
	free_env(&data->env);
	clear_history(); // readline
	close_all_fd();
	exit(g_exit_status);
}

void	free_heredoc(t_cmd *cmd)
{
    while (cmd)
    {
        if (cmd->heredoc_file)
        {
            unlink(cmd->heredoc_file);
            free(cmd->heredoc_file);
            cmd->heredoc_file = NULL;
        }
        cmd = cmd->next;
    }
}

void	minishell_loop(t_data *data)
{
	while (1)
	{
		init_signals_prompt();
		data->line = readline("minishell$ ");
		if (!data->line)
		{
			exit_minishell(data);
		/* 	ft_putstr_fd("exit\n", 2);
			free_all(data, g_exit_status, true); */
		}
		if (empty_line(data->line))
			continue ;
		add_history(data->line);
		if (!parse_line(data))
			continue ;
		else
			executecommand(data);
		free_heredoc(data->cmd);
		free_token(&data->token);
		free_cmd(&data->cmd);
		free(data->line);
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
	free_env(&data.env);
	//free_all(&data, 0, true);
	close_all_fd();
	clear_history();
	return (0);
}
