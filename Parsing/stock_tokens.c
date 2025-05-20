/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:48:09 by mlavry            #+#    #+#             */
/*   Updated: 2025/05/20 19:09:19 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	init_var(int pos[3], bool *sq, bool *dq)
{
	*sq = false;
	*dq = false;
	pos[0] = 0;
	pos[1] = 0;
	pos[2] = 0;
}

int	handle_splitter(char *line, char **tokens, int *pos)
{
	if (is_space(line[pos[1]]))
	{
		if (pos[1] > pos[0])
			tokens[pos[2]++] = ft_substr(line, pos[0], pos[1] - pos[0]);
		while (is_space(line[pos[1]]))
			pos[1]++;
		pos[0] = pos[1];
		return (1);
	}
	else if (is_operator(line[pos[1]]))
	{
		if (pos[1] > pos[0])
			tokens[pos[2]++] = ft_substr(line, pos[0], pos[1] - pos[0]);
		pos[0] = pos[1];
		while (line[pos[1]] == line[pos[0]])
			pos[1]++;
		tokens[pos[2]++] = ft_substr(line, pos[0], pos[1] - pos[0]);
		pos[0] = pos[1];
		return (1);
	}
	return (0);
}

int	stock_sq(char *line, char **tokens, bool *sq, int *pos)
{
	int	s;

	if (*sq)
	{
		if (pos[1] > pos[0])
			tokens[pos[2]++] = ft_substr(line, pos[0], pos[1] - pos[0]);
		pos[1]++;
		s = pos[1];
		while (line[pos[1]] && line[pos[1]] != '\'')
			pos[1]++;
		if (pos[1] > s)
			tokens[pos[2]++] = ft_substr(line, s, pos[1] - s);
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

int	stock_dq(char *line, char **tokens, bool *dq, int *pos)
{
	int	s;

	if (*dq)
	{
		if (pos[1] > pos[0])
			tokens[pos[2]++] = ft_substr(line, pos[0], pos[1] - pos[0]);
		pos[1]++;
		s = pos[1];
		while (line[pos[1]] && line[pos[1]] != '"')
			pos[1]++;
		if (pos[1] > s)
			tokens[pos[2]++] = ft_substr(line, s, pos[1] - s);
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

char	**line_to_token(char *line)
{
	char	**tokens;
	int		pos[3];
	bool	sq;
	bool	dq;

	init_var(pos, &sq, &dq);
	tokens = malloc(sizeof(char *) * (count_tokens(line) + 1));
	if (!tokens)
		return (NULL);
	while (line[pos[1]])
	{
		quote_choice(&sq, &dq, line[pos[1]]);
		if (!sq && !dq)
		{
			if (handle_splitter(line, tokens, pos))
				continue ;
		}
		if (stock_sq(line, tokens, &sq, pos))
			continue ;
		if (stock_dq(line, tokens, &dq, pos))
			continue ;
		pos[1]++;
	}
	if (pos[1] > pos[0])
		tokens[pos[2]++] = ft_substr(line, pos[0], pos[1] - pos[0]);
	tokens[pos[2]] = NULL;
	return (tokens);
}
