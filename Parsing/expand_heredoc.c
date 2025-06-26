/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 01:28:01 by mlavry            #+#    #+#             */
/*   Updated: 2025/06/27 00:06:53 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_expand_in_hd(t_data *data, int *hd, int i)
{
	bool	sq;
	bool	dq;

	sq = false;
	dq = false;
	data->expand_hd[*hd] = true;
	while (is_space(data->line[i]))
		i++;
	while (data->line[i])
	{
		quote_choice(&sq, &dq, data->line[i]);
		if (!sq && !dq && (is_space(data->line[i])
				|| is_operator(data->line[i])))
			break ;
		if (is_quoted(data->line[i]))
			data->expand_hd[*hd] = false;
		i++;
	}
	(*hd)++;
	return (i);
}

void	mark_heredoc_quotes(t_data *data)
{
	int		i;
	int		hd;
	bool	sq;
	bool	dq;

	i = 0;
	hd = 0;
	sq = false;
	dq = false;
	data->nb_hd = count_heredocs(data->line);
	data->expand_hd = malloc(data->nb_hd * sizeof(bool));
	if (!data->expand_hd)
		malloc_failed(data);
	ft_bzero(data->expand_hd, data->nb_hd * sizeof(bool));
	while (data->line[i])
	{
		quote_choice(&sq, &dq, data->line[i]);
		if (!sq && !dq && data->line[i] == '<' && data->line[i + 1] == '<')
		{
			i += 2;
			i = check_expand_in_hd(data, &hd, i);
			continue ;
		}
		i++;
	}
}

void	replace_dollars_heredocs(t_data *data, char **delim)
{
	char	*src;
	char	*res;
	int		len_buf;

	src = *delim;
	res = ft_strdup("");
	if (!res)
		malloc_failed(data);
	len_buf = 0;
	while (*src)
	{
		if (*src == '$')
		{
			check_dollars(data, &src, &res, &len_buf);
			continue ;
		}
		if (!char_append(&res, &len_buf, *src))
			malloc_failed(data);
		src++;
	}
	free(*delim);
	*delim = res;
}
