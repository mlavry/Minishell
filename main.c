/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:55:00 by mlavry            #+#    #+#             */
/*   Updated: 2025/05/14 19:37:15 by mlavry           ###   ########.fr       */
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

/* int main(int argc, char *argv[], char **envp)
{
	char	*line;

	(void) argv;
	(void) envp;
    if (argc != 1)
	{
        return (0);
	}
	while (1)//si on a un probleme avec la ligne actuelle on peut utiliser continue pour passer a la suivante
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);
		line = readline("minishell$ ");
		if (!line)
		{
			ft_putstr_fd("exit\n", 1);
			break;
		}
		if (*line)
			add_history(line);
		free(line);
	}
	rl_clear_history();
	return (0);
} */

bool	empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
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
	parse_env(envp, &data);
	execshell(&data.env);
	emptyenv(&data.env);
	while (1)
	{
		//setup signal
		data.line = readline("minishell$ ");
		if (!data.line)//modifier afin de free tout ce qui est potentiellement malloc et mettre en place un systeme permettant der quitter a la so_long
		{
			ft_putstr_fd("exit\n", 2);
			exit (0);
		}
		if (empty_line(data.line))
			continue ;
		add_history(data.line);
		if (!parse_line(&data, data.line))
			continue ;
		if (data.line[0] == '$')
		{
			if (data.line[1] == '?')
			{
				printf("%d: command not found\n", data.exit_code);
				data.exit_code = 127;
			}
			char *value = getenvp(data.env, data.line + 1);
			if (value)
				printf("bash : %s : command not found\n", value);
			if (value && access(value, X_OK))
				printf("bash : %s no such file or directory\n", value);
		}
		else
			executecommand(&data);
	}
	clear_history();
	return (0);
}
