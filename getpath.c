/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 21:43:31 by aboutale          #+#    #+#             */
/*   Updated: 2025/03/26 21:43:32 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_absolute_path(char *cmd)
{
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
	}
	return (NULL);
}

char	*find_cmd_path(char *cmd)
{
	char	*path;
	char	**token;
	char	*full_path;
	int		i;

	i = 0;
	path = getenv("PATH");
	if (!path)
		return (free(path), NULL);
	token = ft_split(path, ':');
	while (token[i])
	{
		full_path = malloc(ft_strlen(token[i]) + ft_strlen(cmd) + 2);
		if (!full_path)
			break ;
		ft_strcpy(full_path, token[i]);
		ft_strcat(full_path, "/");
		ft_strcat(full_path, cmd);
		if (access(full_path, X_OK) == 0)
			return (free_split(token), full_path);
		free(full_path);
		i++;
	}
	free_split(token);
	return (NULL);
}

char	*getpath(char *cmd, t_cmd *cmds)
{
	char	*fullpath;

	fullpath = get_absolute_path(cmd);
	if (fullpath)
		return (fullpath);
	else
		cmds->g_exit = 127;
	return (free(fullpath), find_cmd_path(cmd));
}
/* 
void	exit_status(t_cmd *cmd)
{

	if (cmd->g_exit == 0)
		printf("0: command not found\n");
	else if (cmd->g_exit == 127)
		printf("127: command not found\n");
	else if (cmd->g_exit == )

} */

/* 
void error_message(t_cmd *cmd, const char *info)
{
    if (cmd->g_exit == 127)
        printf("bash: %s: command not found\n", info);
    else if (cmd->g_exit == 126)
        printf("bash: %s: Permission denied\n", info);
    else if (cmd->g_exit == 2)
        printf("bash: syntax error near unexpected token `%s'\n", info);
    else if (cmd->g_exit == 1)
        printf("bash: %s\n", info); // erreur générique, message déjà préparé
    // Tu peux étendre ici selon les codes que tu utilises
} */
