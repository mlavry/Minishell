/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 21:47:12 by aboutale          #+#    #+#             */
/*   Updated: 2025/04/28 17:50:15 by mlavry           ###   ########.fr       */
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

void	existing_value(t_env **env_list, char *name, char *value)
{
	char	*existing_value;

	existing_value = getenvp(*env_list, name);
	if (existing_value)
	{
		if (value)
			update_env_var(env_list, name, value);
	}
	else
	{
		if (value)
			add_env_var(env_list, name, value);
		else
			add_env_var(env_list, name, "");
	}
}

void	built_export2(t_env **env_list, char **args)
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
			printf("bash: export: `%s': not a valid identifier\n", name);
			free(name);
			free(value);
			i++;
			continue ;
		}
		existing_value(env_list, name, value);
		free(name);
		free(value);
		i++;
	}
}

void	builtin_export(t_env **env_list, char **args)
{
	if (!args[1])
		built_export(*env_list);
	else
		built_export2(env_list, args);
}
