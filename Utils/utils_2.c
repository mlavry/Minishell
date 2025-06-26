/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:46:33 by mlavry            #+#    #+#             */
/*   Updated: 2025/06/26 17:30:50 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	is_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

void	handle_operator(char *line, char **temp, int *pos)
{
	pos[0] = pos[1];
	while (line[pos[1]] == line[pos[0]])
		pos[1]++;
	*temp = ft_substr(line, pos[0], pos[1] - pos[0]);
	pos[0] = pos[1];
}

void	skip_leading_spaces(char *line, int *pos)
{
	while (is_space(line[pos[1]]))
		pos[1]++;
}

int	free_ret(char *ptr)
{
	if (ptr)
		free(ptr);
	return (1);
}
