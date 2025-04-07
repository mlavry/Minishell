/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <taaikiazerolier@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:55:00 by mlavry            #+#    #+#             */
/*   Updated: 2025/04/07 21:36:27 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_replace_line("", 0);
		if (rl_on_new_line() != 0)
			ft_putstr_fd("Error: problem with new line\n", 2);
		rl_redisplay();
	}
}

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

void	init_data(t_data *data, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	data->env = NULL;
	data->exit_code = 0;
}

bool	empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if	(i == (int)ft_strlen(line))
	{
		free(line);
		return (true);
	}
	return (false);
}

int	main(int argc, char *argv[], char **envp)
{
	char	*line;
	t_data	data;

	(void)envp;
	init_data(&data, argc, argv);

	//Creer l'environnement et si sa echoue free les erreurs potentielles
	parse_env(envp, &data);
	/* printf("%s", data.env->value); */
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)//modifier afin de free tout ce qui est potentiellement malloc et mettre en place un systeme permettant der quitter a la so_long
		{
			ft_putstr_fd("exit\n", 2);
			exit (0);
		}
		if (empty_line(line))
			continue;
		if (!parse_line(&data, line))
			continue;
		if (*line)
			add_history(line);
	}
	rl_clear_history();
	return (0);
}
