/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:16:31 by aboutale          #+#    #+#             */
/*   Updated: 2025/06/13 13:25:56 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*find_env_var(t_env *env_list, char *name)
{
	while (env_list != NULL)
	{
		if (ft_strcmp(env_list->name, name) == 0)
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}

int	ft_atoi_safe(const char *str, int *out)
{
	int			i;
	int			sign;
	int			digit;
	long long	res;

	i = 0;
	sign = 1;
	res = 0;
	if (!str || !*str)
		return (0);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		digit = str[i++] - '0';
		res = res * 10 + digit;
		if ((sign == 1 && res > INT_MAX) || (sign == -1 && (-res) < INT_MIN))
			return (0);
	}
	*out = res * sign;
	return (1);
}

void	shlvl_verification(t_env *shlvl, int *lvl)
{
	if (ft_isnumeric(shlvl->value) && ft_atoi_safe(shlvl->value, lvl))
	{
		if (*lvl >= 999)
		{
			(*lvl)++;
			ft_putstr_fd("warning: shell level ", 2);
			ft_putnbr_fd(*lvl, 2);
			ft_putstr_fd(" too high, resetting to 1\n", 2);
			*lvl = 1;
		}
		else if (*lvl < 0)
			*lvl = 0;
		else
			(*lvl)++;
	}
}

void	add_pwd(t_env **env_list, t_data *data, char *cwd)
{
	t_env	*pwd;

	pwd = find_env_var(*env_list, "PWD");
	if (!pwd)
		add_env_var(data, env_list, "PWD", cwd);
	free(cwd);
}

void	execshell(t_data *data, t_env **env_list)
{
	t_env	*shlvl;
	int		lvl;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		malloc_failed(data);
	shlvl = find_env_var(*env_list, "SHLVL");
	if (!shlvl)
	{
		add_env_var(data, env_list, "SHLVL", "1");
		return ;
	}
	else
	{
		lvl = 1;
		shlvl_verification(shlvl, &lvl);
		free(shlvl->value);
		shlvl->value = ft_itoa(lvl);
		if (!shlvl->value)
			malloc_failed(data);
	}
	add_pwd(env_list, data, cwd);
}
