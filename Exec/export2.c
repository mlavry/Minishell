/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 21:47:12 by aboutale          #+#    #+#             */
/*   Updated: 2025/05/13 22:40:30 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_env_var(t_data *data, char *name, char *value)
{
	t_env	*current;

	current = data->env;
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

void	updatepwd(t_data *data, char *oldpath)
{
	char	newpwd[100];
	t_env	*old;
	t_env	*pwd;

	getcwd(newpwd, sizeof(newpwd));
	old = find_env_var(data->env, "OLDPWD");
	if (old)
	{
		free(old->value);
		old->value = ft_strdup(oldpath);
	}
	else
		add_env_var(data, "OLDPWD", oldpath);
	pwd = find_env_var(data->env, "PWD");
	if (pwd)
	{
		free(pwd->value);
		pwd->value = strdup(newpwd);
	}
	else
		add_env_var(data, "PWD", newpwd);
}

void	existing_value(t_data *data, char *name, char *value)
{
	char	*existing_value;

	existing_value = getenvp(data->env, name);
	if (existing_value)
	{
		if (value)
			update_env_var(data, name, value);
	}
	else
	{
		if (value)
			add_env_var(data, name, value);
		else
			add_env_var(data, name, "");
	}
}

void	built_export2(t_data *data, char **args)
{
	int		i;
	char	*arg;
	char	*name;
	char	*value;

	i = 1;
	while (args[i])
	{
		arg = args[i];
		name = extract_name(arg);
		value = extract_value(arg);
		if (!validate_export_name(name))
		{
			if (name && name[0] == '\0')
				printf("bash: export: `': not a valid identifier\n");
			else
				printf("bash: export: `%s': not a valid identifier\n", arg);
			free(name);
			free(value);
			i++;
			continue ;
		}
		existing_value(data, name, value);
		free(name);
		free(value);
		i++;
	}
}

void	builtin_export(t_data *data, t_cmd *cmd)
{
	if (!cmd->args[1])
		built_export(data);
	else
		built_export2(env_list, cmd->args);
}
