/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 21:21:34 by mlavry            #+#    #+#             */
/*   Updated: 2025/06/26 17:55:53 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	quote_choice(bool *sq, bool *dq, char c)
{
	if ((c == '\'' || c == '"') && !*sq && !*dq)
	{
		if (c == '\'' && !*dq)
			*sq = true;
		if (c == '"' && !*sq)
			*dq = true;
	}
	else if (c == '\'' || c == '"')
	{
		if (c == '\'' && !*dq)
			*sq = false;
		if (c == '"' && !*sq)
			*dq = false;
	}
}

int	open_quote(char *line)
{
	bool	sq;
	bool	dq;
	int		i;

	sq = false;
	dq = false;
	i = 0;
	while (line[i])
	{
		quote_choice(&sq, &dq, line[i]);
		i++;
	}
	if (sq || dq)
	{
		g_exit_status = 2;
		ft_putstr_fd("open quote\n", 2);
		return (1);
	}
	return (0);
}

int	is_quoted(char c)
{
	if (c == '\'')
		return (1);
	if (c == '"')
		return (2);
	return (0);
}
