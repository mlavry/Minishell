/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <taaikiazerolier@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:55:00 by mlavry            #+#    #+#             */
/*   Updated: 2025/03/26 20:21:21 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

int main(int argc, char *argv[], char **envp)
{
	char	*line;

	(void) argv;
	(void) envp;
    if (argc != 1)
	{
        return (0);
	}
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break;
		if (*line)
			add_history(line);
		free(line);
	}
	return (0);
}
