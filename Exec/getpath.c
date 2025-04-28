/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 21:43:31 by aboutale          #+#    #+#             */
/*   Updated: 2025/04/28 17:50:21 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		return (NULL);
	token = ft_split(path, ':');
	while (token[i])
	{
		full_path = malloc(ft_strlen(token[i]) + strlen(cmd) + 2);
		if (!full_path)
			break ;
		ft_strcpy(full_path, token[i]);
		ft_strcat(full_path, "/");
		ft_strcat(full_path, cmd);
		if (access(full_path, X_OK) == 0)
			return (free(token[i]), free(token), full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*getpath(char *cmd)
{
	char	*fullpath;

	fullpath = get_absolute_path(cmd);
	if (fullpath)
		return (fullpath);
	else
		g_exit = 127;
	return (find_cmd_path(cmd));
}
