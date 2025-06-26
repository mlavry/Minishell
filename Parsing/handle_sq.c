/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sq.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 03:36:37 by mlavry            #+#    #+#             */
/*   Updated: 2025/06/26 03:37:31 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	skip_dup_quotes(char *line, int *pos)
{
	while (is_quoted(line[pos[1]]) && is_quoted(line[pos[1] + 1])
		&& line[pos[1]] == line[pos[1] + 1])
		pos[1] += 2;
}

static bool	handle_sq_operator(char *line, char **tokens, int *pos, bool *sq)
{
	if (is_operator(line[pos[1]]) && check_operators(line, tokens, pos))
	{
		pos[1]++;
		*sq = false;
		return (true);
	}
	return (false);
}

static char	*capture_sq_content(char *line, int *pos, bool *sq)
{
	char	*temp;
	bool	dq;

	dq = false;
	quote_choice(sq, &dq, line[pos[1]]);
	while (line[pos[1]] && *sq)
	{
		pos[1]++;
		quote_choice(sq, &dq, line[pos[1]]);
	}
	if (pos[1] > pos[0])
		temp = ft_substr(line, pos[0], pos[1] - pos[0]);
	else
		temp = ft_strdup("");
	return (temp);
}

int	handle_sq(char *line, char **tokens, bool *sq, int *pos)
{
	char	*temp;

	if (!*sq)
		return (0);
	pos[1]++;
	pos[0] = pos[1];
	if (handle_sq_operator(line, tokens, pos, sq))
		return (1);
	temp = capture_sq_content(line, pos, sq);
	pos[1]++;
	skip_dup_quotes(line, pos);
	pos[1]++;
	if (handle_sq_operator(line, tokens, pos, sq))
		return (1);
	pos[1]--;
	if (!is_space(line[pos[1]]) && !is_operator(line[pos[1]]))
		temp = check_next(line, temp, pos);
	tokens[pos[2]++] = temp;
	pos[0] = pos[1];
	return (1);
}
