/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_tokens_joined.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 03:19:33 by mlavry            #+#    #+#             */
/*   Updated: 2025/06/26 22:57:00 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_dq_joined(char *line, char *old_chain, bool *dq, int *pos)
{
	char	*temp;
	char	*res;

	temp = extract_dq(line, pos, dq);
	pos[1]++;
	while (line[pos[1]] && line[pos[1] + 1]
		&&is_quoted(line[pos[1]]) && is_quoted(line[pos[1] + 1])
		&& line[pos[1]] == line[pos[1] + 1])
		pos[1] += 2;
	if (!temp)
		return (old_chain);
	res = ft_strjoin(old_chain, temp);
	free(old_chain);
	free(temp);
	if (!is_space(line[pos[1]]) && !is_operator(line[pos[1]]))
		res = check_next(line, res, pos);
	pos[0] = pos[1];
	return (res);
}

char	*handle_sq_joined(char *line, char *old_chain, bool *sq, int *pos)
{
	char	*temp;
	char	*res;

	temp = extract_sq(line, pos, sq);
	pos[1]++;
	while (line[pos[1]] && line[pos[1] + 1]
		&& is_quoted(line[pos[1]]) && is_quoted(line[pos[1] + 1])
		&& line[pos[1]] == line[pos[1] + 1])
		pos[1] += 2;
	if (!temp)
		return (old_chain);
	res = ft_strjoin(old_chain, temp);
	free(old_chain);
	free(temp);
	if (!is_space(line[pos[1]]) && !is_operator(line[pos[1]]))
		res = check_next(line, res, pos);
	pos[0] = pos[1];
	return (res);
}

char	*handle_chain_joined(char *line, char *old_chain, int *pos)
{
	char	*temp;
	char	*res;

	temp = extract_chain(line, pos);
	while (line[pos[1]] && line[pos[1] + 1]
		&& is_quoted(line[pos[1]]) && is_quoted(line[pos[1] + 1])
		&& line[pos[1]] == line[pos[1] + 1])
		pos[1] += 2;
	if (!temp)
		return (old_chain);
	res = ft_strjoin(old_chain, temp);
	free(old_chain);
	free(temp);
	if (!is_space(line[pos[1]]) && !is_operator(line[pos[1]]))
		res = check_next(line, res, pos);
	pos[0] = pos[1];
	return (res);
}
