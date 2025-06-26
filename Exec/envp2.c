/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:13:05 by aboutale          #+#    #+#             */
/*   Updated: 2025/04/29 19:42:32 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	emptyenv(t_data *data, t_env **env_list)
{
	char	*cwd;
	t_env	*pwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		malloc_failed(data);
	if (*env_list == NULL)
	{
		add_env_var(data, env_list, "PWD", cwd);
		add_env_var(data, env_list, "PATH", "/usr/bin:/bin");
	}
	pwd = find_env_var(*env_list, "PWD");
	if (pwd && pwd->value)
		chdir(pwd->value);
	free(cwd);
}

char	*getenvp(t_env *list, char *name)
{
	while (list)
	{
		if (ft_strcmp(list->name, name) == 0)
			return (list->value);
		list = list->next;
	}
	return (NULL);
}

void	swap_env(t_env *a, t_env *b)
{
	char	*tmp;

	tmp = a->name;
	a->name = b->name;
	b->name = tmp;
	tmp = a->value;
	a->value = b->value;
	b->value = tmp;
}

void	sort_env(t_env **env_list)
{
	t_env	*current ;
	t_env	*nextnode;
	int		swap;

	swap = 1;
	while (swap)
	{
		swap = 0;
		current = *env_list;
		while (current->next)
		{
			nextnode = current->next;
			if (ft_strcmp(current->name, nextnode->name) > 0)
			{
				swap_env(current, nextnode);
				swap = 1;
			}
			current = current->next;
		}
	}
}

void	builtin_export(t_data *data, t_env **env_list, t_cmd *cmd)
{
	if (!cmd->args[1])
		built_export(data, *env_list);
	else
		built_export2(data, env_list, cmd->args);
}
