/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 21:47:49 by mlavry            #+#    #+#             */
/*   Updated: 2025/05/20 19:07:21 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	space_and_operator_check(char *line, int *pos)
{
	if (is_space(line[pos[1]]))
	{
		if (pos[1] > pos[0])
			pos[2]++;
		while (is_space(line[pos[1]]))
			pos[1]++;
		pos[0] = pos[1];
		return (1);
	}
	else if (is_operator(line[pos[1]]))
	{
		if (pos[1] > pos[0])
			pos[2]++;
		while (line[pos[1]] == line[pos[0]])
			pos[1]++;
		pos[2]++;
		pos[0] = pos[1];
		return (1);
	}
	return (0);
}

static void	init_var(int pos[3], bool *sq, bool *dq)
{
	pos[0] = 0;
	pos[1] = 0;
	pos[2] = 0;
	*sq = false;
	*dq = false;
}

int	is_sq(char *line, bool *sq, int *pos)
{
	int	s;

	if (*sq)
	{
		if (pos[1] > pos[0])
			pos[2]++;
		pos[1]++;
		s = pos[1];
		while (line[pos[1]] && line[pos[1]] != '\'')
			pos[1]++;
		if (pos[1] > s)
			pos[2]++;
		if (line[pos[1]] == '\'')
		{
			*sq = false;
			pos[1]++;
		}
		pos[0] = pos[1];
		return (1);
	}
	return (0);
}

int	is_dq(char *line, bool *dq, int *pos)
{
	int	s;

	if (*dq)
	{
		if (pos[1] > pos[0])
			pos[2]++;
		pos[1]++;
		s = pos[1];
		while (line[pos[1]] && line[pos[1]] != '"')
			pos[1]++;
		if (pos[1] > s)
			pos[2]++;
		if (line[pos[1]] == '"')
		{
			*dq = false;
			pos[1]++;
		}
		pos[0] = pos[1];
		return (1);
	}
	return (0);
}

int	count_tokens(char *line)
{
	int		pos[3];
	bool	sq;
	bool	dq;

	init_var(pos, &sq, &dq);
	while (line[pos[1]])
	{
		quote_choice(&sq, &dq, line[pos[1]]);
		if (is_sq(line, &sq, pos))
			continue ;
		if (is_dq(line, &dq, pos))
			continue ;
		if (!sq && !dq)
		{
			if (space_and_operator_check(line, pos))
				continue ;
		}
		pos[1]++;
	}
	if (pos[1] > pos[0])
		pos[2]++;
	return (pos[2]);
}
