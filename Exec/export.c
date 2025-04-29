/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 20:41:49 by aboutale          #+#    #+#             */
/*   Updated: 2025/04/29 19:42:40 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	validate_export_name(char *name)
{
	int	i;

	i = 1;
	if (!name || *name == '\0')
		return (0);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

char	*extract_name(char *arg)
{
	char	*sign;

	sign = ft_strchr(arg, '=');
	if (!arg || *arg == '\0')
		return (NULL);
	if (!sign)
		return (ft_strdup(arg));
	return (ft_substr(arg, 0, sign - arg));
}

char	*extract_value(char *arg)
{
	char	*sign;

	sign = ft_strchr(arg, '=');
	if (!arg || *arg == '\0')
		return (NULL);
	if (!sign)
		return (ft_strdup(""));
	return (ft_strdup(sign + 1));
}

t_env	*copyenvlist(t_env *env_list)
{
	t_env	*newlist;
	t_env	*current;

	newlist = NULL;
	current = env_list;
	while (current)
	{
		add_env_var(&newlist, current->name, current->value);
		current = current->next;
	}
	return (newlist);
}

void	built_export(t_env *env_list)
{
	t_env	*sortedlist;
	t_env	*current;

	sortedlist = copyenvlist(env_list);
	sort_env(&sortedlist);
	current = sortedlist;
	while (current)
	{
		if (current->value == NULL || current->value[0] == '\0')
			printf("declare -x %s\n", current->name);
		else
			printf("declare -x %s=\"%s\"\n", current->name, current->value);
		current = current->next;
	}
	free_env_list(sortedlist);
}
