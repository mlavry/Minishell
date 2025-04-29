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
	t_env *env_list = NULL;
	t_cmd cmd;
	char *line;
	cmd.g_exit = 0;
	if (argc != 1)
		exit(0);

	parse_env(envp, &env_list);
	execshell(&env_list);
	//emptyenv(&env_list);
	while (1)
	{
		line = readline(PROMPT);
		if (line[0] == '\0')
		{
			cmd.g_exit = 127;
			free(line);
			continue ;
		}
		add_history(line);
		if (line[0] == '$')
		{
			if (line[1] == '?')
			{
				printf("%d: command not found\n", cmd.g_exit);
				cmd.g_exit = 127;
			}
			char *value = getenvp(env_list, line + 1);
			if (value)
				printf("bash : %s : command not founnd\n", value);
			if (value && access(value, X_OK))
				printf("bash : %s no such file or directory\n", value);
			//else if (access(value, X_OK) != 0)
			//	printf("bash : %s Persmission denied\n", value);
		}
		else
			executecommand(env_list, line, &cmd);
		free(line);
	}
	free_env_list(env_list);
	//free_split()
	clear_history();
	return 0;
}


