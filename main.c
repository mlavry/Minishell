/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:04:40 by aboutale          #+#    #+#             */
/*   Updated: 2025/03/24 19:04:41 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int main(int argc, char **argv, char **envp)
{
	(void)argv;
	t_env *list = NULL;
	t_cmd cmd;
	char *line;

	if (argc != 1)
		exit(0);
/* 
	cmd.name = NULL;
    cmd.args = NULL;
    cmd.fd_in = 0;
    cmd.fd_out = 1;
    cmd.next = NULL; */

	parse_env(envp, &list);
	while (1)
	{

		line = readline(PROMPT);
		if (line[0] == '\0')
		{
			free(line);
			continue ;
		}
		add_history(line);
		if (line[0] == '$')
		{
			char *value = getenvp(list, line + 1);
			if (value)
				printf("shellmini : %s : command not founnd\n", value);
		}
		else 
			executecommand(list, line, envp,&cmd);
		free(line);
	}
}


