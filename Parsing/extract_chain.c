/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_chain.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 03:29:26 by mlavry            #+#    #+#             */
/*   Updated: 2025/06/26 03:31:38 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*extract_dq(char *line, int *pos, bool *dq)
{
	bool	sq;

	sq = false;
	*dq = true;
	pos[1]++;
	pos[0] = pos[1];
	quote_choice(&sq, dq, line[pos[1]]);
	while (line[pos[1]] && *dq)
	{
		pos[1]++;
		quote_choice(&sq, dq, line[pos[1]]);
	}
	if (pos[1] > pos[0])
		return (ft_substr(line, pos[0], pos[1] - pos[0]));
	return (NULL);
}

char	*extract_sq(char *line, int *pos, bool *sq)
{
	bool	dq;

	dq = false;
	*sq = true;
	pos[1]++;
	pos[0] = pos[1];
	quote_choice(sq, &dq, line[pos[1]]);
	while (line[pos[1]] && *sq)
	{
		pos[1]++;
		quote_choice(sq, &dq, line[pos[1]]);
	}
	if (pos[1] > pos[0])
		return (ft_substr(line, pos[0], pos[1] - pos[0]));
	return (NULL);
}

char	*extract_chain(char *line, int *pos)
{
	bool	sq;
	bool	dq;

	sq = false;
	dq = false;
	pos[0] = pos[1];
	quote_choice(&sq, &dq, line[pos[1]]);
	while (line[pos[1]] && !sq && !dq && !is_space(line[pos[1]])
		&& !is_operator(line[pos[1]]))
	{
		pos[1]++;
		quote_choice(&sq, &dq, line[pos[1]]);
	}
	if (pos[1] > pos[0])
		return (ft_substr(line, pos[0], pos[1] - pos[0]));
	return (NULL);
}
