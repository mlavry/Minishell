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
/* void	add_env_var(t_data *data, t_env **env_list, char *name, char *value)
{
	t_env	*new_var;
	t_env	*tmp;

	new_var = malloc(sizeof(t_env));
	if (!new_var)
	{
		free(name);
		malloc_failed(data);
	}
	new_var->name = ft_strdup(name);
	new_var->value = ft_strdup(value);
	if (!new_var->name || !new_var->value)
	{
		free(name);
		free_env(&new_var);
		malloc_failed(data);
	}
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
} */


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
		free(name);
		free_env(&new_var);
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
/* 
void	copy_env(t_env *tmp, int count, char **envp)
{
	int		i;
	size_t	len;

	i = 0;
	while (i < count)
	{
		if (tmp->value == NULL)
		{
			tmp = tmp->next;
			continue ; // ne pas inclure cette variable dans envp
		}
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
} */

/* int count_env_vars(t_env *env_list)
{
    int count = 0;
    while (env_list)
    {
        if (env_list->value != NULL)
            count++;
        env_list = env_list->next;
    }
    return count;
}

char **convert_env(t_env *env_list)
{
    int count = count_env_vars(env_list);
    char **envp = malloc((count + 1) * sizeof(char *));
    int i = 0;
    
    if (!envp)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    while (env_list)
    {
        if (env_list->value != NULL)
        {
            size_t len = ft_strlen(env_list->name) + ft_strlen(env_list->value) + 2;
            envp[i] = malloc(len);
            if (!envp[i])
            {
                perror("malloc");
                exit(EXIT_FAILURE);
            }
            ft_strcpy(envp[i], env_list->name);
            ft_strcat(envp[i], "=");
            ft_strcat(envp[i], env_list->value);
            i++;
        }
        env_list = env_list->next;
    }
    envp[i] = NULL;
    return envp;
} */


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
		free(name);
		i++;
	}
}
