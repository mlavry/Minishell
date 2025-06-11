/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 21:47:12 by aboutale          #+#    #+#             */
/*   Updated: 2025/05/07 00:30:59 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* void update_env_var(t_env **env_list, char *name, char *value)
{
    t_env *current = *env_list;

	printf("update_env_var: name='%s', value='%s'\n", name, value ? value : "NULL");
    while (current)
    {
        if (ft_strcmp(current->name, name) == 0)
        {
            free(current->value);
            if (value)
                current->value = ft_strdup(value);
            else
                current->value = ft_strdup("");  // valeur vide si NULL
            return;
        }
        current = current->next;
    }
} */

void	update_env_var(t_env **env_list, char *name, char *value)
{
	t_env	*current;

	current = *env_list;
	while (current)
	{
		/* if (current->value == NULL)
			return ; */
		if (ft_strcmp(current->name, name) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
}

void	update_env_paths(t_env **env_list, char *oldpath, char *newpwd)
{
	t_env	*old;
	t_env	*pwd;

	old = find_env_var(*env_list, "OLDPWD");
	pwd = find_env_var(*env_list, "PWD");

	if (old)
	{
		free(old->value);
		old->value = ft_strdup(oldpath);
	}
	if (newpwd && pwd)
	{
		free(pwd->value);
		pwd->value = ft_strdup(newpwd);
	}
}

void	updatepwd(t_data *data, t_env **env_list, char *oldpath)
{
	char	*newpwd;

	newpwd = getcwd(NULL, 0);
	if (!newpwd)
	{
		perror("cd: error retrieving current directory");
		data->exit_code = 1;
		update_env_paths(env_list, oldpath, NULL);
		return ;
	}
	update_env_paths(env_list, oldpath, newpwd);
	free(newpwd);
}


/* void updatepwd(t_data *data, t_env **env_list, char *oldpath)
{
    char *newpwd;
    t_env *old;
    t_env *pwd;

    newpwd = getcwd(NULL, 0);
    if (!newpwd)
    {
        perror("cd: error retrieving current directory");
        data->exit_code = 1;
        old = find_env_var(*env_list, "OLDPWD");
        if (old)
        {
            free(old->value);
            old->value = ft_strdup(oldpath);
        }
        return;
    }
    old = find_env_var(*env_list, "OLDPWD");
    if (old)
    {
        free(old->value);
        old->value = ft_strdup(oldpath);
    }
    pwd = find_env_var(*env_list, "PWD");
    if (pwd)
    {
        free(pwd->value);
        pwd->value = strdup(newpwd);
    }
    free(newpwd);
} */


void	existing_value(t_data *data, t_env **env_list, char *name, char *value)
{
	t_env	*existing;
	char	*copied_value;

	existing = find_env_var(*env_list, name);
	if (existing)
	{
		if (value)
		{
			free(existing->value);
			existing->value = ft_strdup(value);
			if (!existing->value)
				malloc_failed(data);
		}
	}
	else
	{
		copied_value = NULL;
		if (value)
		{
			copied_value = ft_strdup(value);
			if (!copied_value)
				malloc_failed(data);
		}
		add_env_var(data, env_list, ft_strdup(name), copied_value);
	}
}

void	increment_and_free(int *i, char *value, char *name)
{
	free(name);
	free(value);
	(*i)++;
}

int	is_concatenation(char *str)
{
	char	*eq;

	eq = ft_strchr(str, '=');
	if (!eq || eq == str)
		return (0);
	return (*(eq - 1) == '+');
}

int	loop(t_env *current, char *new_value, char *var_name)
{
	char	*joined;

	while (current)
	{
		if (ft_strcmp(current->name, var_name) == 0)
		{
			if (current->value)
				joined = ft_strjoin(current->value, new_value);
			else
				joined = ft_strdup(new_value);

			free(current->value);
			current->value = joined;
			return (1);
		}
		current = current->next;
	}
	return (0);
}

void	ft_concatenation(char *str, t_env **env_list, t_data *data)
{
	char	*equal_sign;
	char	*var_name;
	char	*new_value;
	t_env	*current;

	var_name = NULL;
	new_value = NULL;
	equal_sign = ft_strchr(str, '=');
	if (equal_sign && equal_sign > str && *(equal_sign - 1) == '+')
	{
		var_name = ft_substr(str, 0, equal_sign - str - 1);
		new_value = ft_strdup(equal_sign + 1);
	}
	current = *env_list;
	if (!loop(current, new_value, var_name))
		existing_value(data, env_list, var_name, new_value);
	free(var_name);
	free(new_value);
}


void	built_export2(t_data *data, t_env **env_list, char **args)
{
	int		i;
	char	*name;
	char	*value;

	i = 1;
	while (args[i])
	{
		if (is_concatenation(args[i]))
		{
			ft_concatenation(args[i], env_list, data);
			i++;
			continue ;
		}
		name = extract_name(args[i]);
		value = extract_value(args[i]);
		if (!name || !validate_export_name(name))
		{
			printf("export: `%s': not a valid identifier\n", args[i]);
			data->exit_code = 1;
			increment_and_free(&i, value, name);
			continue ;
		}
		existing_value(data, env_list, name, value);
		increment_and_free(&i, value, name);
	}
}
