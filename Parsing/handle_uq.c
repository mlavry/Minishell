/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_uq.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:55:58 by mlavry            #+#    #+#             */
/*   Updated: 2025/06/26 20:57:33 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	handle_unquoted_operator(char *line, char **tokens, int *pos)
{
	char	*temp;

	if (!is_operator(line[pos[1]]))
		return (false);
	if (pos[1] > pos[0])
		tokens[pos[2]++] = ft_substr(line, pos[0], pos[1] - pos[0]);
	handle_operator(line, &temp, pos);
	tokens[pos[2]++] = temp;
	return (true);
}

static bool	mid_quoted_operator(char *line, char **tokens, int *pos)
{
	bool	sq;
	bool	dq;

	if (is_quoted(line[pos[1]]) && is_operator(line[pos[1] + 1])
		&& (is_space(line[pos[1] - 1]) || !line[pos[1] - 1]))
	{
		pos[1]++;
		if (check_operators(line, tokens, pos))
		{
			sq = false;
			dq = false;
			quote_choice(&sq, &dq, line[pos[1]]);
			pos[1]++;
			return (true);
		}
		pos[1]--;
	}
	return (false);
}

static bool	trailing_operator(char *line, char **tokens, int *pos)
{
	bool	sq;
	bool	dq;

	if (line[pos[1] - 1] && line[pos[1]] && is_operator(line[pos[1]])
		&& (is_space(line[pos[1] - 1]) || !line[pos[1] - 1])
		&& check_operators(line, tokens, pos))
	{
		sq = false;
		dq = false;
		quote_choice(&sq, &dq, line[pos[1]]);
		pos[1]++;
		return (true);
	}
	return (false);
}

static char	*capture_bare_word(char *line, int *pos)
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

int	handle_unquoted(char *line, char **tokens, int *pos)
{
	char	*temp;

	temp = NULL;
	skip_leading_spaces(line, pos);
	temp = capture_bare_word(line, pos);
	if (handle_unquoted_operator(line, tokens, pos))
		return (free_ret(temp));
	if (mid_quoted_operator(line, tokens, pos))
		return (free_ret(temp));
	if (!temp && line[pos[1]])
		temp = ft_strdup("");
	skip_dup_quotes(line, pos);
	pos[1]++;
	if (trailing_operator(line, tokens, pos))
		return (free_ret(temp));
	pos[1]--;
	if (temp)
	{
		if (!is_space(line[pos[1]]) && !is_operator(line[pos[1]]))
			temp = check_next(line, temp, pos);
		tokens[pos[2]++] = temp;
	}
	pos[0] = pos[1];
	return (1);
}
