/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:55:00 by mlavry            #+#    #+#             */
/*   Updated: 2025/06/16 23:43:10 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

/*void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_replace_line("", 0);
		if (rl_on_new_line() != 0)
			ft_putstr_fd("Error: problem with new line\n", 2);
		rl_redisplay();
	}
}*/

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

int	main(int argc, char *argv[], char **envp)
{
	t_data	data;

	init_data(&data, argc, argv, envp);
	if (!envp || !*envp || !envp[0])
		emptyenv(&data, &data.env);
	else
		parse_env(envp, &data);
	execshell(&data, &data.env);
	init_signals_prompt();
	while (1)
	{
		data.line = readline("minishell$ ");
		if (!data.line)
		{
			ft_putstr_fd("exit\n", 2);
			free_all(&data, g_exit_status, true);
			exit (0);
		}
		if (empty_line(data.line))
			continue ;
		add_history(data.line);
		if (!parse_line(&data))
			continue ;
		else
			executecommand(&data);
		free_token(&data.token);
		free_cmd(&data.cmd);
		free(data.line);
	}
	free_all(&data, 0, true);
	clear_history();
	return (0);
}
