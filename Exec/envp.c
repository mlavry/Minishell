/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:43:10 by aboutale          #+#    #+#             */
/*   Updated: 2025/06/03 20:37:30 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*create_env_var(t_data *data, char *name, char *value)
{
	t_env	*new_var;

	new_var = malloc(sizeof(t_env));
	if (!new_var)
	{
		free(name);
		malloc_failed(data);
	}
	new_var->name = ft_strdup(name);
	new_var->value = ft_strdup(value);
	if (!new_var->name || (value != NULL && !new_var->value))
	{
		if (new_var->name)
        	free(new_var->name);
    	if (new_var->value)
        	free(new_var->value);
    	free(new_var);
		//free(name);
		//free_env(&new_var);
		malloc_failed(data);
	}
	new_var->next = NULL;
	return (new_var);
}

void	add_env_var(t_data *data, t_env **env_list, char *name, char *value)
{
	t_env	*new_var;
	t_env	*tmp;

	new_var = create_env_var(data, name, value);
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

void	copy_env(t_env *tmp, char **envir)
{
	int		i;
	size_t	len;

	i = 0;
	while (tmp)
	{
		if (tmp->value != NULL)
		{
			len = ft_strlen(tmp->name) + ft_strlen(tmp->value) + 2;
			envir[i] = malloc(len);
			if (!envir[i])
			{
				perror("malloc");
				exit(EXIT_FAILURE);
			}
			ft_strcpy(envir[i], tmp->name);
			ft_strcat(envir[i], "=");
			ft_strcat(envir[i], tmp->value);
			i++;
		}
		tmp = tmp->next;
	}
}

char	**convert_env(t_env *env_list)
{
	int		count;
	t_env	*tmp;
	char	**envir;

	tmp = env_list;
	count = 0;
	while (tmp)
	{
		if (tmp->value != NULL)
			count++;
		tmp = tmp->next;
	}
	envir = malloc((count + 1) * sizeof(char *));
	if (!envir)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	tmp = env_list;
	copy_env(env_list, envir);
	envir[count] = NULL;
	return (envir);
}

void	parse_env(char **envp, t_data *data)
{
	int		i;
	char	*name;
	char	*value;
	char	*equal_pos;

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
		add_env_var(data, &data->env, name, value);
		printf(">> ENV ALLOCATED: %s\n",value);
		free(name);
		i++;
	}
}
