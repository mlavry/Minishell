/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 22:20:48 by aboutale          #+#    #+#             */
/*   Updated: 2025/06/03 21:02:04 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_a_directory(char *path, char **args, t_data *data)
{
	struct stat	sb;

	if (!args[0] || args[0][0] == '\0')
	{
		printf("minishell: command not found\n");
		data->exit_code = 127;
		free(path);
		return (true);
	}
	if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
	{
		printf("bash: %s: Is a directory\n", args[0]);
		free(path);
		data->exit_code = 126;
		return (true);
	}
	return (false);
}

void	exec_builtin_redirection(t_data *data)
{
	int	saved_in;
	int	saved_out;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (data->cmd->fd_in != STDIN_FILENO)
	{
		dup2(data->cmd->fd_in, STDIN_FILENO);
		close(data->cmd->fd_in);
	}
	if (data->cmd->fd_out != STDOUT_FILENO)
	{
		dup2(data->cmd->fd_out, STDOUT_FILENO);
		close(data->cmd->fd_out);
	}
	exec_builtin(data);
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
}

void	executecommand(t_data *data)
{
	if (!data || !data->line || !data->env)
		return ;
	if (data->cmd->fd_in == -1 || data->cmd->fd_out == -1)
	{
		data->exit_code = 1;
		return ;
	}
	if (data->cmd->next)
		exec_pipe(data->cmd, data);
	else if (isbuiltin(data))
	{
		if (!ft_strcmp(data->cmd->args[0], "exit"))
			builtin_exit(data);
		else
			exec_builtin_redirection(data);
	}
	else if (data->cmd->args && data->cmd->args[0])
		exec_extern_command(data->cmd->args, data->env, data);
	else
	{
		if (data->cmd->fd_in != STDIN_FILENO)
		{
			close(data->cmd->fd_in);
			data->cmd->fd_in =STDIN_FILENO;
		}
		if (data->cmd->fd_out != STDOUT_FILENO)
		{
			close(data->cmd->fd_out);
			data->cmd->fd_out = STDOUT_FILENO;
		}
		while(wait(NULL) > 0)
			;
	}
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
