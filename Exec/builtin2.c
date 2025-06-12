/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 21:42:28 by aboutale          #+#    #+#             */
/*   Updated: 2025/06/12 02:34:28 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	emptyenv(t_data *data, t_env **env_list)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		malloc_failed(data);
	if (*env_list == NULL)
	{
		add_env_var(data, env_list, "PWD", cwd);
		add_env_var(data, env_list, "SHLVL", "1");
	}
	free(cwd);
}

void	built_path(char *newpath, t_data *data)
{
	char		cwd[1024];
	struct stat	sb;

	if (access(newpath, F_OK) != 0)
	{
		printf("cd: %s: No such file or directory\n", newpath);
		data->exit_code = 1;
		return ;
	}
	if (stat(newpath, &sb) != 0 || !S_ISDIR(sb.st_mode))
	{
		printf("bash: cd: %s: Not a directory\n", newpath);
		data->exit_code = 1;
		return ;
	}
	if (access(newpath, X_OK) != 0)
	{
		printf("bash: cd: %s: Permission denied\n", newpath);
		data->exit_code = 126;
		return ;
	}
	getcwd(cwd, sizeof(cwd));
	chdir(newpath);
	updatepwd(data, &data->env, cwd);
}

static char	*handle_cd_null(t_data *data)
{
	const char	*home;

	home = getenv("HOME");
	if (!home)
	{
		printf("cd: HOME not set\n");
		data->exit_code = 1;
		return (NULL);
	}
	return ((char *)home);
}

static char *handle_cd_oldpwd(t_data *data, bool *must_free, char *newpath)
{
	t_env *old;

	old = find_env_var(data->env, "OLDPWD");
	if (!old || !old->value)
	{
		printf("cd: OLDPWD not set\n");
		data->exit_code = 1;
		return (NULL);
	}
	printf("%s\n", old->value);
	newpath = ft_strdup(old->value);
	if (!newpath)
		malloc_failed(data);
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
		printf("cd: HOME not set\n");
		data->exit_code = 1;
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

	must_free = false;
	if (newpath == NULL)
		newpath = handle_cd_null(data);
	else if (newpath[0] == '-')
		newpath = handle_cd_oldpwd(data, &must_free, newpath);
	else if (newpath[0] == '~')
		newpath = handle_cd_home(newpath, data, &must_free);
	if (newpath)
		built_path(newpath, data);
	if (must_free)
		free(newpath);
}

void	unset(t_env **env_list, char *name )
{
	t_env	*current;
	t_env	*previous;

	current = *env_list;
	previous = NULL;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			if (previous)
				previous->next = current->next;
			else
				*env_list = current->next;
			free(current->name);
			free(current->value);
			free(current);
			break ;
		}
		previous = current;
		current = current->next;
	}
}

void	builtin_unset(t_env **env_list, t_cmd *cmd)
{
	char	*name;
	int		i;

	if (!cmd->args || !cmd->args[1])
		return ;
	i = 1;
	while (cmd->args[i])
	{
		name = cmd->args[i];
		unset(env_list, name);
		i++;
	}
}
