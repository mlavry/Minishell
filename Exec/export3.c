/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:24:58 by aboutale          #+#    #+#             */
/*   Updated: 2025/06/16 23:42:22 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	export_error(char *name, char *value, char **args, int *i)
{
	ft_putstr_fd("export: ", 2);
	print_error(args[*i], "not a valid identifier\n");
	g_exit_status = 1;
	increment_and_free(i, value, name);
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
			export_error(name, value, args, &i);
			continue ;
		}
		existing_value(data, env_list, name, value);
		increment_and_free(&i, value, name);
	}
}
