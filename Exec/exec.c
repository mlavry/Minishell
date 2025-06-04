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

void	parent_and_wait(int status, char *path, t_data *data, pid_t pid)
{
	waitpid(pid, &status, 0);
	free(path);
	if (data->cmd->fd_in != STDIN_FILENO)
		close(data->cmd->fd_in);
	if (data->cmd->fd_out != STDOUT_FILENO)
		close(data->cmd->fd_out);
	if (WIFEXITED(status))
		data->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		data->exit_code = 128 + WTERMSIG(status);
}

void	extern_childprocess(t_data *data, char *path, t_env *env, char **args)
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
	execve(path, args, convert_env(env));
	perror("execve");
	exit(127);
}

bool	is_a_directory(char *path, char **args, t_data *data)
{
	struct stat	sb;

	if (!args[0] || args[0][0] == '\0')
	{
		printf("minishell: command not found\n");
		data->exit_code = 127;
		free(path);
		return true;
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

bool	have_no_permission(char *cmd_path, t_data *data)
{
	if (access(cmd_path, F_OK) != 0)
	{
		printf("minishell: %s: No such file or directory\n", cmd_path);
		data->exit_code = 127;
		return true;
	}
	if (access(cmd_path, X_OK) != 0)
	{
		printf("minishell: %s: Permission denied\n", cmd_path);
		data->exit_code = 126;
		return true;
	}
	return false;
}

void	exec_extern_command(char **args, t_env *env, t_data *data)
{
	pid_t		pid;
	int			status;
	char		*path;

	status = 0;
	if (ft_strchr(args[0], '/'))
		path = ft_strdup(args[0]);
	else
		path = getpath(args[0], data);
	if (!path)
	{
		if (ft_strcmp(args[0], "\\n") == 0)
		{
			printf("n : command not found \n");
			data->exit_code = 127;
		}
		else
			printf("%s: command not found\n", args[0]);
		free(path);
		data->exit_code = 127;
		return ;
	}
	if (is_a_directory(path, args, data))
		return ;
	if (have_no_permission(path, data))
		return ;
	pid = fork();
	if (pid == -1)
		return (perror("fork"), data->exit_code = 1, free(path));
	if (pid == 0)
		extern_childprocess(data, path, env, args);
	else
		parent_and_wait(status, path, data, pid);
}
