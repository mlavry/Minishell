/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:43:10 by aboutale          #+#    #+#             */
/*   Updated: 2025/05/13 22:35:25 by mlavry           ###   ########.fr       */
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

void	add_env_var(t_data *data, char *name, char *value)
{
	t_env	*new_var;
	t_env	*tmp;

	new_var = malloc(sizeof(t_env));
	if (!new_var)
		malloc_failed(data);
	new_var->name = ft_strdup(name);
	if (!new_var->name)
		malloc_failed(data);
	new_var->value = ft_strdup(value);
	if (!new_var->value)
		malloc_failed(data);
	new_var->next = NULL;
	if (!data->env)
	{
		data->env = new_var;
		return ;
	}
	tmp = *data->env;
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

void	parse_env(char **envp, t_data *data)
{
	int		i;
	char	*name;
	char	*value;
	char	*equal_pos;
void	updatepwd(t_env **env_list, char *oldpath);
	i = 0;
	while (envp[i])
	{
		equal_pos = ft_strchr(envp[i], '=');
		if (!equal_pos)
		{
			i++;
			continue ;
		}
		name = ft_substr(envp[i], 0, equal_pos - envp[i]);
		if (!name)
			malloc_failed(data);
		value = equal_pos + 1;
		add_env_var(data, name, value);
		free(name);
		i++;
	}
}
