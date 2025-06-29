/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 21:42:28 by aboutale          #+#    #+#             */
/*   Updated: 2025/06/27 01:04:52 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_cd_errors(char *newpath)
{
	struct stat	sb;

	if (access(newpath, F_OK) != 0)
	{
		ft_putstr_fd("cd: ", 2);
		print_error(newpath, "No such file or directory\n");
		g_exit_status = 1;
		return (0);
	}
	if (stat(newpath, &sb) != 0 || !S_ISDIR(sb.st_mode))
	{
		ft_putstr_fd("cd: ", 2);
		print_error(newpath, "Not a directory\n");
		g_exit_status = 1;
		return (0);
	}
	if (access(newpath, X_OK) != 0)
	{
		ft_putstr_fd("cd: ", 2);
		print_error(newpath, "Permission denied\n");
		g_exit_status = 126;
		return (0);
	}
	return (1);
}

static char	*handle_cd_null(void)
{
	const char	*home;

	home = getenv("HOME");
	if (!home)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		g_exit_status = 1;
		return (NULL);
	}
	return ((char *)home);
}

static char	*handle_cd_oldpwd(t_data *data, bool *must_free, char *newpath)
{
	t_env	*old;

	old = find_env_var(data->env, "OLDPWD");
	if (!old || !old->value)
	{
		ft_putstr_fd("cd: OLDPWD not set\n", 2);
		g_exit_status = 1;
		return (NULL);
	}
	if (access(old->value, F_OK) != 0)
	{
		ft_putstr_fd("cd: ", 2);
		print_error(old->value, "No such file or directory\n");
		g_exit_status = 1;
		return (NULL);
	}
	printf("%s\n", old->value);
	newpath = ft_strdup(old->value);
	if (!newpath)
	{
		free(newpath);
		malloc_failed(data);
	}
	*must_free = true;
	return (newpath);
}

static char	*handle_cd_home(char *newpath, t_data *data, bool *must_free)
{
	const char	*home;
	char		*expanded_path;

	home = getenv("HOME");
	if (!home)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		g_exit_status = 1;
		return (NULL);
	}
	expanded_path = malloc(ft_strlen(home) + ft_strlen(newpath));
	if (!expanded_path)
		malloc_failed(data);
	ft_strcpy(expanded_path, home);
	ft_strcat(expanded_path, newpath + 1);
	newpath = expanded_path;
	*must_free = true;
	return (expanded_path);
}

void	builtin_cd(char *newpath, t_data *data)
{
	bool		must_free;
	int			count;

	must_free = false;
	count = 0;
	while (data->cmd->args[count])
		count++;
	if (count > 2)
	{
		ft_putstr_fd(*data->cmd->args, 2);
		ft_putstr_fd(": too many arguments\n", 2);
		g_exit_status = 1;
		return ;
	}
	if (newpath == NULL)
		newpath = handle_cd_null();
	else if (newpath[0] == '-')
		newpath = handle_cd_oldpwd(data, &must_free, newpath);
	else if (newpath[0] == '~')
		newpath = handle_cd_home(newpath, data, &must_free);
	if (newpath)
		built_path(newpath, data);
	if (must_free)
		free(newpath);
}
