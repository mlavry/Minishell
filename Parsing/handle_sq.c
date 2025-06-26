/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sq.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 03:36:37 by mlavry            #+#    #+#             */
/*   Updated: 2025/06/27 00:31:23 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skip_dup_quotes(char *line, int *pos)
{
	while (line[pos[1]] && line[pos[1] + 1]
		&& is_quoted(line[pos[1]]) && is_quoted(line[pos[1] + 1])
		&& line[pos[1]] == line[pos[1] + 1])
		pos[1] += 2;
}

// int	handle_sq(char *line, char **tokens, bool *sq, int *pos)
// {
// 	char	*temp;
// 	bool	dq;

// 	dq = false;
// 	temp = NULL;
// 	if (!*sq)
// 		return (0);
// 	pos[1]++;
// 	pos[0] = pos[1];
// 	if (is_operator(line[pos[1]]) && check_operators(line, tokens, pos))
// 	{
// 		pos[1]++;
// 		(*sq) = false;
// 		return (1);
// 	}
// 	quote_choice(sq, &dq, line[pos[1]]);
// 	while (line[pos[1]] && *sq)
// 	{
// 		pos[1]++;
// 		quote_choice(sq, &dq, line[pos[1]]);
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
// 		(*sq) = false;
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

static char	*sq_extract(char *line, bool *sq, int *pos)
{
	bool	dq;
	char	*token;

	dq = false;
	quote_choice(sq, &dq, line[pos[1]]);
	while (line[pos[1]] && *sq)
	{
		pos[1]++;
		quote_choice(sq, &dq, line[pos[1]]);
	}
	if (pos[1] > pos[0])
		token = ft_substr(line, pos[0], pos[1] - pos[0]);
	else
		token = ft_strdup("");
	if (!token)
		return (NULL);
	return (token);
}

static int	handle_sq_body(char *line, char **tokens, bool *sq, int *pos)
{
	char	*temp;

	temp = sq_extract(line, sq, pos);
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
		(*sq) = false;
		return (1);
	}
	pos[1]--;
	if (!is_space(line[pos[1]]) && !is_operator(line[pos[1]]))
		temp = check_next(line, temp, pos);
	tokens[pos[2]++] = temp;
	pos[0] = pos[1];
	return (1);
}

int	handle_sq(char *line, char **tokens, bool *sq, int *pos)
{
	if (!*sq)
		return (0);
	pos[1]++;
	pos[0] = pos[1];
	if (is_operator(line[pos[1]]) && check_operators(line, tokens, pos))
	{
		pos[1]++;
		(*sq) = false;
		return (1);
	}
	return (handle_sq_body(line, tokens, sq, pos));
}
