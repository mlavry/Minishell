/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 21:47:12 by aboutale          #+#    #+#             */
/*   Updated: 2025/06/16 23:45:18 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_env_var(t_env **env_list, char *name, char *value)
{
	t_env	*current;

	current = *env_list;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
}

void	update_env_paths(t_data *data, t_env **env, char *oldpath, char *newpwd)
{
	t_env	*old;
	t_env	*pwd;

	old = find_env_var(*env, "OLDPWD");
	pwd = find_env_var(*env, "PWD");
	if (old)
	{
		free(old->value);
		old->value = ft_strdup(oldpath);
		if (!old->value)
			malloc_failed(data);
	}
	else
		add_env_var(NULL, env, "OLDPWD", oldpath);
	if (newpwd && pwd)
	{
		free(pwd->value);
		pwd->value = ft_strdup(newpwd);
		if (!pwd->value)
			malloc_failed(data);
	}
}

void	updatepwd(t_data *data, t_env **env_list, char *oldpath)
{
	char	*newpwd;

	newpwd = getcwd(NULL, 0);
	if (!newpwd)
	{
		ft_putstr_fd("cd: error retrieving current directory:", 2);
		ft_putstr_fd("No such file or directory\n", 2);
		g_exit_status = 1;
		update_env_paths(data, env_list, oldpath, NULL);
		return ;
	}
	update_env_paths(data, env_list, oldpath, newpwd);
	free(newpwd);
}

void	dontexist_value(t_data *data, t_env **env_list, char *name, char *value)
{
	char	*copied_name;
	char	*copied_value;

	copied_name = ft_strdup(name);
	if (!copied_name)
		malloc_failed(data);
	copied_value = NULL;
	if (value)
	{
		copied_value = ft_strdup(value);
		if (!copied_value)
		{
			free(copied_name);
			malloc_failed(data);
		}
	}
	add_env_var(data, env_list, copied_name, copied_value);
	free(copied_name);
	if (copied_value)
		free(copied_value);
}

void	existing_value(t_data *data, t_env **env_list, char *name, char *value)
{
	t_env	*existing;

	existing = find_env_var(*env_list, name);
	if (existing)
	{
		if (value)
		{
			free(existing->value);
			existing->value = ft_strdup(value);
			if (!existing->value)
				malloc_failed(data);
		}
	}
	else
		dontexist_value(data, env_list, name, value);
}
