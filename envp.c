/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:43:10 by aboutale          #+#    #+#             */
/*   Updated: 2025/05/14 18:24:06 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	add_env_var(t_env **env_list, char *name, char *value)
{
	t_env	*new_var;
	t_env	*tmp;

	new_var = malloc(sizeof(t_env));
	if (!new_var)
		return ;
	new_var->name = ft_strdup(name);
	if (!new_var->name)
		return ;
	new_var->value = ft_strdup(value);
	if (!new_var->value)
		return ;
	new_var->next = NULL;
	if (!*env_list)
	{
		*env_list = new_var;
		return ;
	}
	tmp = *env_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_var;
}

void	copy_env(t_env *tmp, int count, char **envp)
{
	int		i;
	size_t	len;

	i = 0;
	while (i < count)
	{
		len = ft_strlen(tmp->name) + ft_strlen(tmp->value) + 2;
		envp[i] = malloc(len);
		if (!envp[i])
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		ft_strcpy(envp[i], tmp->name);
		ft_strcat(envp[i], "=");
		ft_strcat(envp[i], tmp->value);
		tmp = tmp->next;
		i++;
	}
}

char	**convert_env(t_env *env_list)
{
	int		count;
	t_env	*tmp;
	char	**envp;

	tmp = env_list;
	count = 0;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	envp = malloc((count + 1) * sizeof(char *));
	if (!envp)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	tmp = env_list;
	copy_env(tmp, count, envp);
	envp[count] = NULL;
	return (envp);
}

void	parse_env(char **envp, t_data *env_list)
{
	int		i;
	char	*name;
	char	*value;
	char	*equal_pos;

	i = 0;
	while (envp[i])
	{
		equal_pos = strchr(envp[i], '=');
		if (!equal_pos)
		{
			i++;
			continue ;
		}
		name = ft_substr(envp[i], 0, equal_pos - envp[i]);
		if (!name)
			return ;
		value = equal_pos + 1;
		add_env_var(&env_list->env, name, value);
		free(name);
		i++;
	}
}
