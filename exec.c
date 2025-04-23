/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 20:57:16 by aboutale          #+#    #+#             */
/*   Updated: 2025/04/20 20:57:17 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_extern_command(char **args, t_env *env_list)
{
	pid_t	pid;
	int		status;
	char	*path;

	path = getpath(args[0]);
	if (!path)
	{
		printf("bash : %s command not found\n", args[0]);
		g_exit = 127;
		return ;
	}
	pid = fork();
	if (pid == -1)
		return (perror("fork"), g_exit = 1, free(path));
	if (pid == 0)
	{
		execve(path, args, convert_env(env_list));
		perror("execve");
		exit(127);
	}
	else
		waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit = 128 + WTERMSIG(status);
}

void	executecommand(t_env *env_list, char *line, t_cmd *cmd)
{
	char	**args;
	int		i;

	i = 0;
	args = ft_split(line, ' ');
	if (!args[0])
	{
		free(args);
		return ;
	}
	cmd->name = args[0];
	cmd->args = args;
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	cmd->next = NULL;
	if (!isbuiltin(cmd, env_list, cmd->args))
		exec_extern_command(cmd->args, env_list);
	while (args[i])
		free(args[i++]);
	free(args);
}

t_env	*find_env_var(t_env *env_list, char *name)
{
	while (env_list != NULL)
	{
		if (ft_strcmp(env_list->name, name) == 0)
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}

void	execshell( t_env **env_list)
{
	t_env	*shlvl;

	shlvl = find_env_var(*env_list, "SHLVL");
	if (!shlvl)
		return ;
	if (shlvl)
	{
		int level = atoi(shlvl->value);
		level++;
		char *new_val = ft_itoa(level);
		if (new_val)
		{
			free(shlvl->value);
			shlvl->value = new_val;
		}
	}
}

