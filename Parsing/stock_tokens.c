/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:48:09 by mlavry            #+#    #+#             */
/*   Updated: 2025/05/22 19:36:38 by mlavry           ###   ########.fr       */
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

/*static void	check_after_quotes(char *line, char **tokens, int *pos)
{
	int	start;
	while (line[pos[1]] &&
    	(!is_space(line[pos[1]]) && !is_operator(line[pos[1]])))
	{
    	if (line[pos[1]] == '\'' || line[pos[1]] == '"')
    	{
        	char lim = line[pos[1]];
			pos[1]++;
			start = pos[1];
        	while (line[pos[1]] && line[pos[1]] != lim)
            	pos[1]++;
        	if (line[pos[1]] == lim)
            	pos[1]++;
    	}
    	else
        	pos[1]++;
	}
	// ensuite on ne fait QU’UNE SEULE fusion :
	char *suffix = ft_substr(line, start, pos[1] - start);
	char *joined = ft_strjoin(tokens[pos[2] - 1], suffix);
	free(tokens[pos[2] - 1]);
	free(suffix);
	tokens[pos[2] - 1] = joined;
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
		check_after_quotes(line, tokens, pos);
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
		check_after_quotes(line, tokens, pos);
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
	tokens = malloc(sizeof(char *) * (2000)); count_tokens(line) + 1
	if (!tokens)
		return (NULL);
	while (line[pos[1]])
	{
		quote_choice(&sq, &dq, line[pos[1]]);
		if (!sq && !dq && handle_splitter(line, tokens, pos))
			continue ;
		if (stock_sq(line, tokens, &sq, pos)
			|| stock_dq(line, tokens, &dq, pos))
			continue ;
		pos[1]++;
	}
	if (pos[1] > pos[0])
		tokens[pos[2]++] = ft_substr(line, pos[0], pos[1] - pos[0]);
	tokens[pos[2]] = NULL;
	return (tokens);
}*/

/*int	stock_sq(char *line, char **tokens, bool *sq, int *pos)
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
		check_after_quotes(line, tokens, pos);
		pos[0] = pos[1];
		return (1);
	}
	return (0);
}*/

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
	if (line[pos[1]] == '\'')
		pos[1]++;
	if (temp)
		res = ft_strjoin(old_chain, temp);
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
	quote_choice(sq, &dq, line[pos[1]]);
	while (line[pos[1]] && *sq)
	{
		pos[1]++;
		quote_choice(sq, &dq, line[pos[1]]);
	}
	if (pos[1] > pos[0])
		temp = ft_substr(line, pos[0], pos[1] - pos[0]);
	pos[1]++;
	quote_choice(sq, &dq, line[pos[1]]);
	if (*sq)
		temp = handle_sq_joined(line, temp, sq, pos);
	tokens[pos[2]++] = temp;
	pos[0] = pos[1];
	return (1);
}

char	**line_to_token(char *line)
{
	char	**tokens;
	int		pos[3];
	bool	sq;
	bool	dq;

	init_var(pos, &sq, &dq);
	tokens = malloc(sizeof(char *) * 2000);
	if (!tokens)
		return (NULL);
	while (line[pos[1]])
	{
		quote_choice(&sq, &dq, line[pos[1]]);
		if (handle_sq(line, tokens, &sq, pos))
			continue ;
		pos[1]++;
	}
	tokens[pos[2]] = NULL;
	return (tokens);
}
