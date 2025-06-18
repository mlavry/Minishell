/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_to_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 21:47:49 by mlavry            #+#    #+#             */
/*   Updated: 2025/06/17 23:37:20 by mlavry           ###   ########.fr       */
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
