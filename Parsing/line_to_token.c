/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 21:47:49 by mlavry            #+#    #+#             */
/*   Updated: 2025/06/26 00:27:10 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	skip_spaces(char *line, size_t *i)
{
	while (line[*i] && is_space(line[*i]))
		(*i)++;
}

static void	skip_operator(char *line, size_t *i)
{
	char	op;

	op = line[*i];
	while (line[*i] && line[*i] == op)
		(*i)++;
}

static void	consume_word(char *line, size_t *i, bool *sq, bool *dq)
{
	while (line[*i])
	{
		quote_choice(sq, dq, line[*i]);
		if (!*sq && !*dq && (is_space(line[*i]) || is_operator(line[*i])))
			break ;
		(*i)++;
	}
}

int	count_tokens(char *line)
{
	size_t	i;
	int		tokens;
	bool	sq;
	bool	dq;

	i = 0;
	tokens = 0;
	sq = false;
	dq = false;
	while (line && line[i])
	{
		skip_spaces(line, &i);
		if (!line[i])
			break ;
		tokens++;
		if (!sq && !dq && is_operator(line[i]))
			skip_operator(line, &i);
		else
			consume_word(line, &i, &sq, &dq);
	}
	return (tokens);
}

int	count_heredocs(char *line)
{
	int		i;
	int		nb;
	bool	sq;
	bool	dq;

	i = 0;
	nb = 0;
	dq = false;
	sq = false;
	while (line[i])
	{
		quote_choice(&sq, &dq, line[i]);
		if (!sq && !dq && line[i] == '<' && line[i + 1] == '<')
		{
			nb++;
			i += 2;
			continue ;
		}
		i++;
	}
	return (nb);
}
