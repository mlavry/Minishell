/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 20:57:16 by aboutale          #+#    #+#             */
/*   Updated: 2025/06/16 23:52:15 by mlavry           ###   ########.fr       */
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
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_status = 128 + WTERMSIG(status);
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

bool	have_no_permission(char *cmd_path)
{
	if (access(cmd_path, F_OK) != 0)
	{
		printf("minishell: %s: No such file or directory\n", cmd_path);
		g_exit_status = 127;
		return (true);
	}
	if (access(cmd_path, X_OK) != 0)
	{
		printf("minishell: %s: Permission denied\n", cmd_path);
		g_exit_status = 126;
		return (true);
	}
	return (false);
}

void	launch_extern_command(char **args, t_env *env, t_data *data)
{
	pid_t	pid;
	int		status;
	char	*path;

	status = 0;
	if (ft_strchr(args[0], '/'))
		path = ft_strdup(args[0]);
	else
		path = getpath(args[0], data);
	if (!path)
	{
		printf("%s: command not found\n", args[0]);
		g_exit_status = 127;
		return ;
	}
	if (is_a_directory(path, args) || have_no_permission(path))
		return (free(path));
	pid = fork();
	if (pid == -1)
		return (perror("fork"), g_exit_status = 1, free(path));
	if (pid == 0)
		extern_childprocess(data, path, env, args);
	else
		parent_and_wait(status, path, data, pid);
}

void	exec_extern_command(char **args, t_env *env, t_data *data)
{
	if (!args || !args[0] || args[0][0] == '\0')
	{
		printf("'' command not found\n");
		g_exit_status = 127;
		return ;
	}
	if (ft_strcmp(args[0], "\\n") == 0)
	{
		printf("n : command not found\n");
		g_exit_status = 127;
		return ;
	}
	launch_extern_command(args, env, data);
}

/* void	exec_extern_command(char **args, t_env *env, t_data *data)
{
	pid_t		pid;
	int			status;
	char		*path;

	status = 0;
	if (!args || !args[0] || args[0][0] == '\0')
	{
		printf("'' command not found\n");
		g_exit_status = 127;
		return ;
	}
	if (ft_strchr(args[0], '/'))
		path = ft_strdup(args[0]);
	else
		path = getpath(args[0], data);
	if (!path)
	{
		if (ft_strcmp(args[0], "\\n") == 0)
		{
			printf("n : command not found \n");
			g_exit_status = 127;
		}
		else
			printf("%s: command not found\n", args[0]);
		free(path);
		g_exit_status = 127;
		return ;
	}
	if (is_a_directory(path, args, data))
	{
		free(path);
		return ;
	}
	if (have_no_permission(path, data))
		return ;
	pid = fork();
	if (pid == -1)
		return (perror("fork"), g_exit_status = 1, free(path));
	if (pid == 0)
		extern_childprocess(data, path, env, args);
	else
		parent_and_wait(status, path, data, pid);
} */
