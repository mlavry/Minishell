/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:48:09 by mlavry            #+#    #+#             */
/*   Updated: 2025/06/26 17:22:40 by mlavry           ###   ########.fr       */
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

// int	handle_unquoted(char *line, char **tokens, int *pos)
// {
// 	char	*temp;
// 	bool	sq;
// 	bool	dq;

// 	temp = NULL;
// 	sq = false;
// 	dq = false;
// 	while (is_space(line[pos[1]]))
// 		pos[1]++;
// 	pos[0] = pos[1];
// 	quote_choice(&sq, &dq, line[pos[1]]);
// 	while (line[pos[1]] && !is_space(line[pos[1]]) && !is_operator(line[pos[1]])
// 		&& !sq && !dq)
// 	{
// 		pos[1]++;
// 		quote_choice(&sq, &dq, line[pos[1]]);
// 	}
// 	if (is_operator(line[pos[1]]))
// 	{
// 		if (pos[1] > pos[0])
// 			tokens[pos[2]++] = ft_substr(line, pos[0], pos[1] - pos[0]);
// 		handle_operator(line, &temp, pos);
// 		tokens[pos[2]++] = temp;
// 		return (1);
// 	}
// 	if (pos[1] > pos[0])
// 		temp = ft_substr(line, pos[0], pos[1] - pos[0]);
// 	if (is_quoted(line[pos[1]]) && is_operator(line[pos[1] + 1])
// 		&& (is_space(line[pos[1] - 1]) || !line[pos[1] - 1]))
// 	{
// 		pos[1]++;
// 		if (check_operators(line, tokens, pos))
// 		{
// 			quote_choice(&sq, &dq, line[pos[1]]);
// 			pos[1]++;
// 			return (1);
// 		}
// 		pos[1]--;
// 	}
// 	if (!temp && line[pos[1]])
// 		temp = ft_strdup("");
// 	while (line[pos[1]] && line[pos[1] + 1]
// 		&& is_quoted(line[pos[1]]) && is_quoted(line[pos[1] + 1])
// 		&& line[pos[1]] == line[pos[1] + 1])
// 		pos[1] = pos[1] + 2;
// 	pos[1]++;
// 	if (line[pos[1] - 1] && line[pos[1]]
// 		&& is_operator(line[pos[1]]) && (is_space(line[pos[1] - 1])
// 			|| !line[pos[1] - 1]) && check_operators(line, tokens, pos))
// 	{
// 		quote_choice(&sq, &dq, line[pos[1]]);
// 		pos[1]++;
// 		return (1);
// 	}
// 	pos[1]--;
// 	if (temp)
// 	{
// 		if (!is_space(line[pos[1]])
// 			&& !is_operator(line[pos[1]]))
// 			temp = check_next(line, temp, pos);
// 		tokens[pos[2]++] = temp;
// 	}
// 	pos[0] = pos[1];
// 	return (1);
// }

char	*check_next(char *line, char *actual_chain, int *pos)
{
	bool	dq;
	bool	sq;
	char	*res;

	dq = false;
	sq = false;
	res = actual_chain;
	quote_choice(&sq, &dq, line[pos[1]]);
	if (sq)
		res = handle_sq_joined(line, actual_chain, &sq, pos);
	else if (dq)
		res = handle_dq_joined(line, actual_chain, &dq, pos);
	else
		res = handle_chain_joined(line, actual_chain, pos);
	return (res);
}

char	**line_to_token(t_data *data)
{
	char	**tokens;
	int		pos[3];
	bool	sq;
	bool	dq;

	init_var(pos, &sq, &dq);
	tokens = malloc(sizeof(char *) * (count_tokens(data->line) + 1));
	if (!tokens)
		return (NULL);
	while (data->line[pos[1]])
	{
		quote_choice(&sq, &dq, data->line[pos[1]]);
		if (!sq && !dq && handle_unquoted(data->line, tokens, pos))
			continue ;
		if (handle_sq(data->line, tokens, &sq, pos)
			|| handle_dq(data->line, tokens, &dq, pos))
			continue ;
		pos[1]++;
	}
	tokens[pos[2]] = NULL;
	return (tokens);
}
