/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dq.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 03:40:17 by mlavry            #+#    #+#             */
/*   Updated: 2025/06/26 23:43:50 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	handle_dq(char *line, char **tokens, bool *dq, int *pos)
// {
// 	char	*temp;
// 	bool	sq;

// 	sq = false;
// 	temp = NULL;
// 	if (!*dq)
// 		return (0);
// 	pos[1]++;
// 	pos[0] = pos[1];
// 	if (is_operator(line[pos[1]]) && check_operators(line, tokens, pos))
// 	{
// 		pos[1]++;
// 		(*dq) = false;
// 		return (1);
// 	}
// 	quote_choice(&sq, dq, line[pos[1]]);
// 	while (line[pos[1]] && *dq)
// 	{
// 		pos[1]++;
// 		quote_choice(&sq, dq, line[pos[1]]);
// 	}
// 	if (pos[1] > pos[0])
// 		temp = ft_substr(line, pos[0], pos[1] - pos[0]);
// 	else
// 		temp = ft_strdup("");
// 	pos[1]++;
// 	while (is_quoted(line[pos[1]]) && is_quoted(line[pos[1] + 1])
// 		&& line[pos[1]] == line[pos[1] + 1])
// 		pos[1] = pos[1] + 2;
// 	pos[1]++;
// 	if (line[pos[1] - 1] && line[pos[1]]
// 		&& is_operator(line[pos[1]]) && (is_space(line[pos[1] - 1])
// 			|| !line[pos[1] - 1]) && check_operators(line, tokens, pos))
// 	{
// 		pos[1]++;
// 		(*dq) = false;
// 		return (1);
// 	}
// 	pos[1]--;
// 	if (!is_space(line[pos[1]])
// 		&& !is_operator(line[pos[1]]))
// 		temp = check_next(line, temp, pos);
// 	tokens[pos[2]++] = temp;
// 	pos[0] = pos[1];
// 	return (1);
// }

static char	*dq_extract(char *line, bool *dq, int *pos)
{
	bool	sq;
	char	*token;

	sq = false;
	quote_choice(&sq, dq, line[pos[1]]);
	while (line[pos[1]] && *dq)
	{
		pos[1]++;
		quote_choice(&sq, dq, line[pos[1]]);
	}
	if (pos[1] > pos[0])
		token = ft_substr(line, pos[0], pos[1] - pos[0]);
	else
		token = ft_strdup("");
	return (token);
}

static int	handle_dq_body(char *line, char **tokens, bool *dq, int *pos)
{
	char	*temp;

	temp = dq_extract(line, dq, pos);
	pos[1]++;
	while (is_quoted(line[pos[1]])
		&& is_quoted(line[pos[1] + 1])
		&& line[pos[1]] == line[pos[1] + 1])
		pos[1] += 2;
	pos[1]++;
	if (line[pos[1] - 1] && line[pos[1]]
		&& is_operator(line[pos[1]])
		&& (is_space(line[pos[1] - 1]) || !line[pos[1] - 1])
		&& check_operators(line, tokens, pos))
	{
		pos[1]++;
		(*dq) = false;
		return (1);
	}
	pos[1]--;
	if (!is_space(line[pos[1]]) && !is_operator(line[pos[1]]))
		temp = check_next(line, temp, pos);
	tokens[pos[2]++] = temp;
	pos[0] = pos[1];
	return (1);
}

int	handle_dq(char *line, char **tokens, bool *dq, int *pos)
{
	if (!*dq)
		return (0);
	pos[1]++;
	pos[0] = pos[1];
	if (is_operator(line[pos[1]]) && check_operators(line, tokens, pos))
	{
		pos[1]++;
		(*dq) = false;
		return (1);
	}
	return (handle_dq_body(line, tokens, dq, pos));
}
