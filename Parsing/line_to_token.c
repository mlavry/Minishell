/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 21:47:49 by mlavry            #+#    #+#             */
/*   Updated: 2025/04/28 16:20:17 by mlavry           ###   ########.fr       */
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

int	space_and_operator_check(int *start, int *i, int *count, char *line)
{
	int	advanced;

	advanced = 0;
	if (is_space(line[*i]))
	{
		if (*i > *start)
			(*count)++;
		while (is_space(line[*i]))
			(*i)++;
		*start = *i;
		advanced = 1;
	}
	else if (is_operator(line[*i]))
	{
		if (*i > *start)
			(*count)++;
		while (line[*i] == line[*start])
			(*i)++;
		(*count)++;
		*start = *i;
		advanced = 1;
	}
	return (advanced);
}

int	count_tokens(char *line)
{
	int		start;
	int		i;
	int		count;
	bool	sq;
	bool	dq;

	start = 0;
	i = 0;
	count = 0;
	sq = false;
	dq = false;
	while (line[i])
	{
		quote_choice(&sq, &dq, line[i]);
		if (!sq && !dq)
		{
			if (space_and_operator_check(&start, &i, &count, line))
				continue ;
		}
		i++;
	}
	if (i > start)
		count++;
	return (count);
}
