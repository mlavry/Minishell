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
/* #include <fcntl.h>

void close_all_fd(void)
{
    int fd = 3;
    while (fd < 1024)
    {
        if (fcntl(fd, F_GETFD) != -1)
            close(fd);
        fd++;
    }
} */



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

/* void	free_cmd(t_cmd **cmd)
{
    t_cmd	*tmp;

    while (*cmd)
    {
        tmp = *cmd;
        *cmd = (*cmd)->next;

        if (tmp->name)
        {
            free(tmp->name);
            tmp->name = NULL;
        }

        if (tmp->args)
        {
            int i = 0;
            while (tmp->args[i])
            {
                free(tmp->args[i]);
                tmp->args[i] = NULL;
                i++;
            }
            free(tmp->args);
            tmp->args = NULL;
        }

        free(tmp);
    }
}  */
/* 
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
		//close_all_fd();
		free(*cmd);
		*cmd = tmp;
	}
	*cmd = NULL;
}   */

/* void	free_cmd(t_cmd **cmd)
{
	t_cmd *tmp;
	t_cmd *next;

	if (!cmd || !*cmd)
		return;
	tmp = *cmd;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->args)
			free_tab(tmp->args); // ta fonction qui libère un tableau de char*
		if (tmp->name)
			free(tmp->name);       // si t'as ce champ
		free(tmp);
		tmp = next;
	}
	*cmd = NULL;
} */


void	free_cmd(t_cmd **cmd)
{
    t_cmd	*tmp;
    t_cmd	*current;

	//tmp = NULL;
    if (!cmd || !*cmd)
        return ;
   // printf("Freeing cmd list...\n");
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
      //  printf("Current cmd: %p\n", (void*)current);
      //  if (current->name)
           // printf("Freeing name: %s\n", current->name), free(current->name);
        if (current->args)
        {
           // printf("Freeing args...\n");
            free_tab(current->args);
        }
		 // ...
        if (current->heredoc_file)
        {
            // Le fichier devrait déjà être unlink, mais au cas où...
            unlink(current->heredoc_file);
            free(current->heredoc_file);
        }
		if (current->infile)
        {
           // printf("Freeing args...\n");
            free(current->infile);
        }
		if (current->outfile)
        {
           // printf("Freeing args...\n");
            free(current->outfile);
        }
		if (current->outfile_append)
        {
           // printf("Freeing args...\n");
            free(current->outfile_append);
        }
       // if (current->fd_in)
          //  printf("Freeing infile: %d\n", current->fd_in);
       // if (current->fd_out)
         //   printf("Freeing outfile: %d\n", current->fd_out);
      //  printf("Freeing command struct\n");
        free(current);
        current = tmp;
    }
    *cmd = NULL;
} 
