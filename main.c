/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:55:00 by mlavry            #+#    #+#             */
/*   Updated: 2025/06/03 20:50:09 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

bool	empty_line(char *line, t_data *data)
{
	int	i;

	i = 0;
/* 	if (line[i] == '>' || line[i] == '<')
    {
		if (is_multiple_append(&line[i]) || is_multiple_heredoc(&line[i]))
		{
			data->exit_code = 2;
			return true;
		}
	}  */
	while (line[i] && (line[i] == ' ' || line[i] == ':' || line[i] == '.'))
	{
		i++;
		data->exit_code = 0;
	}
	if (line[0] == '|')
	{
		printf("bash: syntax error near unexpected token `|'\n");
		data->exit_code = 2;
		return (true);
	}
	if (line[i] == '!')
	{
		i++;
		data->exit_code = 1;
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
	while (1)
	{
		data.line = readline("minishell$ ");
		if (!data.line)
		{
			ft_putstr_fd("exit\n", 2);
			free_all(&data, 0, true);
			exit (0);
		}
		if (empty_line(data.line, &data))
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
