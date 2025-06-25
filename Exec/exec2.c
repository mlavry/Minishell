/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 22:20:48 by aboutale          #+#    #+#             */
/*   Updated: 2025/06/16 23:50:56 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_a_directory(char *path, char **args)
{
	struct stat	sb;

	if (!args || !args[0] || args[0][0] == '\0')
	{
		ft_putstr_fd("minishell: command not found\n", 2);
		g_exit_status = 127;
		free(path);
		return (true);
	}
	if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
	{
		print_error(args[0], "Is a directory\n");
		free(path);
		g_exit_status = 126;
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

void	redirect_file(t_data *data)
{
	if (data->cmd->fd_out != STDOUT_FILENO)
	{
		close(data->cmd->fd_out);
		data->cmd->fd_out = STDOUT_FILENO;
	}
	if (data->cmd->fd_in != STDIN_FILENO)
	{
		close(data->cmd->fd_in);
		data->cmd->fd_in = STDIN_FILENO;
	}
}

void	executecommand(t_data *data)
{
	if (!data || !data->line || !data->env || !data->cmd)
		return ;
	if (data->cmd->fd_in == -1 || data->cmd->fd_out == -1)
	{
		g_exit_status = 1;
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
	else if (!data->cmd->args || !data->cmd->args[0])
		redirect_file(data);
/* 	{
		if (data->cmd->fd_out != STDOUT_FILENO)
		{
			close(data->cmd->fd_out);
			data->cmd->fd_out = STDOUT_FILENO;
		}
		if (data->cmd->fd_in != STDIN_FILENO)
		{
			close(data->cmd->fd_in);
			data->cmd->fd_in = STDIN_FILENO;
		}
	} */
	free_cmd(&data->cmd);
	data->cmd = NULL;
}

// void	executecommand(t_data *data)
// {
// 	if (!data || !data->line || !data->env)
// 		return ;
// 	if (data->cmd->fd_in == -1 || data->cmd->fd_out == -1)
// 	{
// 		g_exit_status = 1;
// 		return ;
// 	}
// 	if (data->cmd->next)
// 		exec_pipe(data->cmd, data);
// 	else if (isbuiltin(data))
// 	{
// 	 	if (!ft_strcmp(data->cmd->args[0], "exit"))
// 			builtin_exit(data);
// 		else 
// 			exec_builtin_redirection(data);
// 	}
// 	else if (!data->cmd->args || !data->cmd->args[0])
// 	{
// 	// Ne pas exécuter, mais si redirection seule, tu crées le fichier vide
// 		if (data->cmd->fd_out != STDOUT_FILENO)
// 		{
// 			write(data->cmd->fd_out, "", 0);
// 			close(data->cmd->fd_out);
// 			data->cmd->fd_out = STDOUT_FILENO;
// 		}
// 		if (data->cmd->fd_in != STDIN_FILENO)
// 		{
// 			close(data->cmd->fd_in);
// 			data->cmd->fd_in = STDIN_FILENO;
// 		}
// 		return ;
// 	}
// 	else if (data->cmd->args && data->cmd->args[0])
// 		exec_extern_command(data->cmd->args, data->env, data);
// 	else
// 	{
// 	 	if (data->cmd->fd_in != STDIN_FILENO)
// 		{
// 			close(data->cmd->fd_in);
// 			data->cmd->fd_in =STDIN_FILENO;
// 		}
// 		if (data->cmd->fd_out != STDOUT_FILENO)
// 		{
// 			close(data->cmd->fd_out);
// 			data->cmd->fd_out = STDOUT_FILENO;
// 		}
// 		while(wait(NULL) > 0)
// 			;
// 		if (data->cmd->fd_in != STDIN_FILENO)
// 		{
//     		close(data->cmd->fd_in);
//    	 		data->cmd->fd_in = STDIN_FILENO;
// 		}
// 		if (data->cmd->fd_out != STDOUT_FILENO)
// 		{
// 			close(data->cmd->fd_out);
// 			data->cmd->fd_out = STDOUT_FILENO;
// 		}
// 	}
//   	free_cmd(&data->cmd);
// 	data->cmd = NULL;  
// 	close_all_fd();
// }

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
