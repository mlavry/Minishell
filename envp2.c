/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:13:05 by aboutale          #+#    #+#             */
/*   Updated: 2025/04/23 21:13:08 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/* void free_envp(char **envp)
{
    for (int i = 0; envp[i] != NULL; i++)
    {
        free(envp[i]);
    }
    free(envp);
}  */

/* void free_env_var(t_env *var)
{
    if (var)
    {
        if (var->name)
            free(var->name);
        if (var->value)
            free(var->value);
        free(var);
    }
} */

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

/* void free_env_list(t_env *env_list)
{
    t_env *tmp;
    while (env_list)
    {
        tmp = env_list;             // Sauvegarde l'élément actuel
        env_list = env_list->next;  // Passe à l'élément suivant
        free_env_var(tmp);          // Libère l'élément actuel
    }
}  */