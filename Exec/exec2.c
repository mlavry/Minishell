/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 22:20:48 by aboutale          #+#    #+#             */
/*   Updated: 2025/05/19 22:20:49 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	if (data->cmd->next)
		exec_pipe(data->cmd, data);
	else if (isbuiltin(data))
		exec_builtin_redirection(data);
	else
	{
		exec_extern_command(data->cmd->args, data->env, data);
		if (data->cmd->fd_in != STDIN_FILENO)
			close(data->cmd->fd_in);
		if (data->cmd->fd_out != STDOUT_FILENO)
			close(data->cmd->fd_out);
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

void	execshell(t_data *data, t_env **env_list)
{
	t_env	*shlvl;
	int		level;
	char	*new_val;

	shlvl = find_env_var(*env_list, "SHLVL");
	if (!shlvl)
		return ;
	if (shlvl)
	{
		level = ft_atoi(shlvl->value);
		if (level >= 999)
		{
			printf("warning: shell level (1000) too high, resetting to 1\n");
			level = 1;
		}
		else
			level++;
		new_val = ft_itoa(level);
		if (!new_val)
			malloc_failed(data);
		free(shlvl->value);
		shlvl->value = new_val;
	}
}
