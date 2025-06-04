/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 23:44:24 by mlavry            #+#    #+#             */
/*   Updated: 2025/06/04 21:12:07 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isnumeric(const char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	while (is_space(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && !is_space(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_operators(char *line, char **tokens, int *pos)
{
 	char	quote_actual;
	int		old_pos;

	old_pos = pos[1] - 1;
	quote_actual = line[pos[1] - 1];
	while (is_operator(line[pos[1]]))
		pos[1]++;
	if (line[pos[1]] == quote_actual && (!line[pos[1] + 1]
			|| is_space(line[pos[1] + 1])))
	{
		tokens[pos[2]++] = ft_substr(line, pos[0] - 1, pos[1] - pos[0] + 2);
		pos[0] = pos[1];
		return (1);
	}
	pos[1] = old_pos;
	pos[0] = pos[1];
	return (0);
}
