/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dq.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 03:40:17 by mlavry            #+#    #+#             */
/*   Updated: 2025/06/26 20:47:45 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	handle_dq_operator(char *line, char **tokens, int *pos, bool *dq)
{
	if (is_operator(line[pos[1]]) && check_operators(line, tokens, pos))
	{
		pos[1]++;
		*dq = false;
		return (true);
	}
	return (false);
}

static char	*capture_dq_content(char *line, int *pos, bool *dq)
{
	char	*temp;
	bool	sq;

	sq = false;
	quote_choice(&sq, dq, line[pos[1]]);
	while (line[pos[1]] && *dq)
	{
		pos[1]++;
		quote_choice(&sq, dq, line[pos[1]]);
	}
	if (pos[1] > pos[0])
		temp = ft_substr(line, pos[0], pos[1] - pos[0]);
	else
		temp = ft_strdup("");
	return (temp);
}

int	handle_dq(char *line, char **tokens, bool *dq, int *pos)
{
	char	*temp;

	temp = NULL;
	if (!*dq)
		return (0);
	pos[1]++;
	pos[0] = pos[1];
	if (handle_dq_operator(line, tokens, pos, dq))
		return (free_ret(temp));
	temp = capture_dq_content(line, pos, dq);
	pos[1]++;
	skip_dup_quotes(line, pos);
	pos[1]++;
	if (handle_dq_operator(line, tokens, pos, dq))
		return (free_ret(temp));
	pos[1]--;
	if (!is_space(line[pos[1]]) && !is_operator(line[pos[1]]))
		temp = check_next(line, temp, pos);
	tokens[pos[2]++] = temp;
	pos[0] = pos[1];
	return (1);
}
