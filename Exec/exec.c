/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 20:57:16 by aboutale          #+#    #+#             */
/*   Updated: 2025/05/14 19:33:51 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



void	extern_childprocess(t_data *data, char *path, t_env *env_list,char **args)
{
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
	execve(path, args, convert_env(env_list));
	perror("execve");
	exit(127);
}


void	exec_extern_command(char **args, t_env *env_list, t_data *data)
{
	pid_t		pid;
	int			status;
	char		*path;
	struct stat	sb;

	status = 0;
	path = getpath(args[0], data);
	if (!path)
	{
		printf("bash : %s: command not found\n", args[0]);
		free(path);
		data->exit_code = 127;
		return ;
	}
	if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
	{
		printf("bash: %s: Is a directory\n", args[0]);
		free(path);
		data->exit_code = 126;
		return ;
	}
	pid = fork();
	if (pid == -1)
		return (perror("fork"), data->exit_code = 1, free(path));
	if (pid == 0)
		extern_childprocess(data, path, env_list, args);
	else
	{
		waitpid(pid, &status, 0);
		free(path);
		if (data->cmd->fd_in != STDIN_FILENO)
			close(data->cmd->fd_in);
		if (data->cmd->fd_out != STDOUT_FILENO)
			close(data->cmd->fd_out);
	}
	if (WIFEXITED(status))
		data->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		data->exit_code = 128 + WTERMSIG(status);
}


void	executecommand(t_data *data)
{
	if (!data || !data->line || !data->env)
		return ;

	if (data->cmd->next)
		exec_pipe(data->cmd, data);
	else if (isbuiltin(data))
	{
		int saved_in = dup(STDIN_FILENO);
		int saved_out = dup(STDOUT_FILENO);

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

void	execshell( t_env **env_list)
{
	t_env	*shlvl;
	int		level;
	char	*new_val ;

	shlvl = find_env_var(*env_list, "SHLVL");
	if (!shlvl)
		return ;
	if (shlvl)
	{
		level = ft_atoi(shlvl->value);
		level++;
		new_val = ft_itoa(level);
		if (new_val)
		{
			free(shlvl->value);
			shlvl->value = new_val;
		}
	}
}
