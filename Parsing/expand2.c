/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 21:48:57 by aboutale          #+#    #+#             */
/*   Updated: 2025/06/26 21:49:00 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	dollar_loop(t_data *data, char *src, char **res, int *len)
{
	bool	sq;
	bool	dq;

	sq = false;
	dq = false;
	while (*src)
	{
		quote_choice(&sq, &dq, *src);
		if (*src == '$' && !dq && !sq)
		{
			if (check_quote_dollars(res, len, &src, data))
				continue ;
		}
		if (*src == '$' && !sq)
		{
			check_dollars(data, &src, res, len);
			continue ;
		}
		if (!char_append(res, len, *src))
			malloc_failed(data);
		src++;
	}
}

void	replace_dollars(t_data *data)
{
	char	*res;
	int		len;

	res = ft_strdup("");
	if (!res)
		malloc_failed(data);
	len = 0;
	dollar_loop(data, data->line, &res, &len);
	free(data->line);
	data->line = res;
}
