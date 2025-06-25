/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 21:47:49 by mlavry            #+#    #+#             */
/*   Updated: 2025/06/25 19:33:09 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_tokens(char *line)
{
	size_t	i = 0;
	int		tokens = 0;
	bool	sq = false;
	bool	dq = false;

	while (line && line[i])
	{
		while (is_space(line[i]))
			i++;
		if (!line[i])
			break ;
		tokens++;
		if (!sq && !dq && is_operator(line[i]))
		{
			char op = line[i];
			while (line[i] == op)
				i++;
		}
		else
		{
			while (line[i])
			{
				quote_choice(&sq, &dq, line[i]);
				if (!sq && !dq && (is_space(line[i]) || is_operator(line[i])))
					break ;
				i++;
			}
		}
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
