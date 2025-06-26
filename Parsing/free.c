/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 22:31:47 by mlavry            #+#    #+#             */
/*   Updated: 2025/06/26 17:59:50 by mlavry           ###   ########.fr       */
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
    t_cmd	*current;

    if (!cmd || !*cmd)
        return ;
    current = *cmd;
    while (current)
    {
		tmp = current->next; 
		if ( current->name)
			free(current->name);
		if (current->fd_in != STDIN_FILENO && current->fd_in > 2)
			close(current->fd_in);
		if (current->fd_out != STDOUT_FILENO && current->fd_out > 2)
			close(current->fd_out);	
        if (current->args)
            free_tab(current->args);
        if (current->heredoc_file)
        {
            unlink(current->heredoc_file);
            free(current->heredoc_file);
		}
		if (current->infile)
            free(current->infile);
		if (current->outfile)
            free(current->outfile);
		if (current->outfile_append)
            free(current->outfile_append);
        free(current);
        current = tmp;
    }
    *cmd = NULL;
}
