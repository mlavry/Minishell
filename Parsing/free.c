/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 22:31:47 by mlavry            #+#    #+#             */
/*   Updated: 2025/05/13 20:29:48 by mlavry           ###   ########.fr       */
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

void	safe_close(int fd)
{
	if (fd > 2)
		close(fd);
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
		safe_close((*cmd)->fd_in);
		safe_close((*cmd)->fd_out);
		free(*cmd);
		*cmd = tmp;
	}
	*cmd = NULL;
}
