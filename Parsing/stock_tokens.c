/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:48:09 by mlavry            #+#    #+#             */
/*   Updated: 2025/06/17 23:59:04 by mlavry           ###   ########.fr       */
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

char *	handle_dq_joined(char *line, char *old_chain, bool *dq, int *pos)
{
	char	*temp;
	char	*res;
	bool	sq = false;

	temp = NULL;
	pos[1]++;
	pos[0] = pos[1];
	*dq = true;
	quote_choice(&sq, dq, line[pos[1]]);
	while (line[pos[1]] && *dq)
	{
		pos[1]++;
		quote_choice(&sq, dq, line[pos[1]]);
	}
	if (pos[1] > pos[0])
		temp = ft_substr(line, pos[0], pos[1] - pos[0]);
	pos[1]++;
	while (is_quoted(line[pos[1]]) && is_quoted(line[pos[1] + 1])
		&& line[pos[1]] == line[pos[1] + 1])
		pos[1] = pos[1] + 2;
	if (temp)
	{
		res = ft_strjoin(old_chain, temp);
		if (!is_space(line[pos[1]])
			&& !is_operator(line[pos[1]]))
			res = check_next(line, res, pos);
	}
	else
		return (old_chain);
	pos[0] = pos[1];
	return (res);
}

char *	handle_sq_joined(char *line, char *old_chain, bool *sq, int *pos)
{
	char	*temp;
	char	*res;
	bool	dq = false;

	temp = NULL;
	pos[1]++;
	pos[0] = pos[1];
	*sq = true;
	quote_choice(sq, &dq, line[pos[1]]);
	while (line[pos[1]] && *sq)
	{
		pos[1]++;
		quote_choice(sq, &dq, line[pos[1]]);
	}
	if (pos[1] > pos[0])
		temp = ft_substr(line, pos[0], pos[1] - pos[0]);
	pos[1]++;
	while (is_quoted(line[pos[1]]) && is_quoted(line[pos[1] + 1])
		&& line[pos[1]] == line[pos[1] + 1])
		pos[1] = pos[1] + 2;
	if (temp)
	{
		res = ft_strjoin(old_chain, temp);
		if (!is_space(line[pos[1]])
			&& !is_operator(line[pos[1]]))
			res = check_next(line, res, pos);
	}
	else
		return (old_chain);
	pos[0] = pos[1];
	return (res);
}

char	*handle_chain_joined(char *line, char *old_chain, int *pos)
{
	char	*temp;
	char	*res;
	bool	dq = false;
	bool	sq = false;

	temp = NULL;
	pos[0] = pos[1];
	quote_choice(&sq, &dq, line[pos[1]]);
	while (line[pos[1]] && !sq && !dq && !is_space(line[pos[1]])
		&& !is_operator(line[pos[1]]))
	{
		pos[1]++;
		quote_choice(&sq, &dq, line[pos[1]]);
	}
	if (pos[1] > pos[0])
		temp = ft_substr(line, pos[0], pos[1] - pos[0]);
	while (is_quoted(line[pos[1]]) && is_quoted(line[pos[1] + 1])
		&& line[pos[1]] == line[pos[1] + 1])
		pos[1] = pos[1] + 2;
	if (temp)
	{
		res = ft_strjoin(old_chain, temp);
		if (!is_space(line[pos[1]])
			&& !is_operator(line[pos[1]]))
			res = check_next(line, res, pos);
	}
	else
		return (old_chain);
	pos[0] = pos[1];
	return (res);
}

int	handle_sq(char *line, char **tokens, bool *sq, int *pos)
{
	char	*temp;
	bool	dq = false;

	temp = NULL;
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
	pos[1]++;
	while (is_quoted(line[pos[1]]) && is_quoted(line[pos[1] + 1])
		&& line[pos[1]] == line[pos[1] + 1])
		pos[1] = pos[1] + 2;
	pos[1]++;
	if (is_operator(line[pos[1]]) && (is_space(line[pos[1] - 1])
			|| !line[pos[1] - 1]) && check_operators(line, tokens, pos))
	{
		pos[1]++;
		(*sq) = false;
		return (1);
	}
	pos[1]--;
	if (!is_space(line[pos[1]])
		&& !is_operator(line[pos[1]]))
		temp = check_next(line, temp, pos);
	tokens[pos[2]++] = temp;
	pos[0] = pos[1];
	return (1);
}

int	handle_dq(char *line, char **tokens, bool *dq, int *pos)
{
	char	*temp;
	bool	sq = false;

	temp = NULL;
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
	pos[1]++;
	while (is_quoted(line[pos[1]]) && is_quoted(line[pos[1] + 1])
		&& line[pos[1]] == line[pos[1] + 1])
		pos[1] = pos[1] + 2;
	pos[1]++;
	if (is_operator(line[pos[1]]) && (is_space(line[pos[1] - 1])
			|| !line[pos[1] - 1]) && check_operators(line, tokens, pos))
	{
		pos[1]++;
		(*dq) = false;
		return (1);
	}
	pos[1]--;
	if (!is_space(line[pos[1]])
		&& !is_operator(line[pos[1]]))
		temp = check_next(line, temp, pos);
	tokens[pos[2]++] = temp;
	pos[0] = pos[1];
	return (1);
}

void	handle_operator(char *line, char **temp, int *pos)
{
	pos[0] = pos[1];
	while (line[pos[1]] == line[pos[0]])
		pos[1]++;
	*temp = ft_substr(line, pos[0], pos[1] - pos[0]);
	pos[0] = pos[1];
}

int	handle_unquoted(char *line, char **tokens, int *pos)
{
	char	*temp;
	bool	sq;
	bool	dq;

	temp = NULL;
	sq = false;
	dq = false;
	while (is_space(line[pos[1]]))
		pos[1]++;
	pos[0] = pos[1];
	quote_choice(&sq, &dq, line[pos[1]]);
	while (line[pos[1]] && !is_space(line[pos[1]]) && !is_operator(line[pos[1]])
		&& !sq && !dq)
	{
		pos[1]++;
		quote_choice(&sq, &dq, line[pos[1]]);
	}
	if (is_operator(line[pos[1]]))
	{
		if (pos[1] > pos[0])
			tokens[pos[2]++] = ft_substr(line, pos[0], pos[1] - pos[0]);
		handle_operator(line, &temp, pos);
		tokens[pos[2]++] = temp;
		return (1);
	}
	if (pos[1] > pos[0])
		temp = ft_substr(line, pos[0], pos[1] - pos[0]);
	if (is_quoted(line[pos[1]]) && is_operator(line[pos[1] + 1])
		&& (is_space(line[pos[1] - 1]) || !line[pos[1] - 1]))
	{
		pos[1]++;
		if (check_operators(line, tokens, pos))
		{
			quote_choice(&sq, &dq, line[pos[1]]);
			pos[1]++;
			return (1);
		}
		pos[1]--;
	}
	if (!temp && line[pos[1]])
		temp = ft_strdup("");
	while (is_quoted(line[pos[1]]) && is_quoted(line[pos[1] + 1])
		&& line[pos[1]] == line[pos[1] + 1])
		pos[1] = pos[1] + 2;
	pos[1]++;
	if (is_operator(line[pos[1]]) && (is_space(line[pos[1] - 1])
			|| !line[pos[1] - 1]) && check_operators(line, tokens, pos))
	{
		quote_choice(&sq, &dq, line[pos[1]]);
		pos[1]++;
		return (1);
	}
	pos[1]--;
	if (temp)
	{
		if (!is_space(line[pos[1]])
			&& !is_operator(line[pos[1]]))
			temp = check_next(line, temp, pos);
		tokens[pos[2]++] = temp;
	}
	pos[0] = pos[1];
	return (1);
}

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
