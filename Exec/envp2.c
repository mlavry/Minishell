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

void	free_env_list(t_env *env_list)
{
	t_env	*tmp;

	while (env_list)
	{
		tmp = env_list;
		free(tmp->name);
		free(tmp->value);
		env_list = env_list->next;
		free(tmp);
	}
}

void	builtin_export(t_data *data, t_env **env_list, t_cmd *cmd)
{
	if (!cmd->args[1])
		built_export(data, *env_list);
	else
		built_export2(data, env_list, cmd->args);
}
