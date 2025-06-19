/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 22:31:47 by mlavry            #+#    #+#             */
/*   Updated: 2025/05/14 18:33:17 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tab(char **tokens)
{
	int	i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

/* void closefd(t_data *data)
{
	if (data->cmd->fd_in != STDIN_FILENO)
		close(data->cmd->fd_in);
	if (data->cmd->fd_out != STDOUT_FILENO)
		close(data->cmd->fd_out);
} */

void	close_all_fd(void)
{
	int	fd;

	fd = 3;
	if (fd > 1024)
		exit(0);
	while (fd < 1024)
	{
		close(fd);
		fd++;
	}
}

void	free_env(t_env **env)
{
	t_env	*tmp;

	if (!env || !*env)
		return ;
	while (*env)
	{
		tmp = (*env)->next;
		if ((*env)->name)
			free((*env)->name);
		if ((*env)->value)
			free((*env)->value);
		free(*env);
		*env = tmp;
	}
	*env = NULL;
}

void	free_token(t_token **token)
{
	t_token	*tmp;

	if (!token || !*token)
		return ;
	while (*token)
	{
		tmp = (*token)->next;
		if ((*token)->str)
			free((*token)->str);
		free(*token);
		*token = tmp;
	}
	*token = NULL;
}

void	free_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;

	if (!cmd || !*cmd)
		return ;
	while (*cmd)
	{
		tmp = (*cmd)->next;
		if ((*cmd)->name)
			free((*cmd)->name);
		if ((*cmd)->args)
			free_tab((*cmd)->args);
		close_all_fd();
		free(*cmd);
		*cmd = tmp;
	}
	*cmd = NULL;
}
