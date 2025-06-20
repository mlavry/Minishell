/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 21:43:31 by aboutale          #+#    #+#             */
/*   Updated: 2025/06/16 23:42:22 by mlavry           ###   ########.fr       */
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

char	*find_cmd_path(char *cmd, t_env *env_list)
{
	char	*path;
	char	**token;
	char	*full_path;
	int		i;

	i = 0;
	path = getenvp(env_list, "PATH");
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
			return (free_tab(token), full_path);
		free(full_path);
		i++;
	}
	free_tab(token);
	return (NULL);
}

char	*getpath(char *cmd, t_data *data)
{
	char	*fullpath;

	fullpath = get_absolute_path(cmd);
	if (fullpath)
		return (fullpath);
	fullpath = find_cmd_path(cmd, data->env);
	if (!fullpath)
		g_exit_status = 127;
	return (fullpath);
}
