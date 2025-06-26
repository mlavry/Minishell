/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:50:04 by aboutale          #+#    #+#             */
/*   Updated: 2025/06/16 23:58:15 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	dollar_exit(char **src, char **res, int *len_buf)
{
	char	*nbr;

	nbr = ft_itoa(g_exit_status);
	if (!nbr)
		return (0);
	if (!str_append(res, len_buf, nbr))
	{
		free(nbr);
		return (0);
	}
	free(nbr);
	*src += 2;
	return (1);
}

int	dollar_var(t_data *data, char **src, char **res, int *len_buf)
{
	size_t	i;
	char	*key;
	char	*value;

	i = 1;
	while ((*src)[i] && (ft_isalnum((*src)[i]) || (*src)[i] == '_'))
		i++;
	if (i <= 1)
		return (0);
	key = ft_substr(*src + 1, 0, i - 1);
	if (!key)
		malloc_failed(data);
	value = getenvp(data->env, key);
	free(key);
	if (value && !str_append(res, len_buf, value))
		malloc_failed(data);
	*src += i;
	return (1);
}

void	check_dollars(t_data *data, char **src, char **res, int *len_buf)
{
	if ((*src)[1] == '?')
	{
		if (!dollar_exit(src, res, len_buf))
			malloc_failed(data);
		return ;
	}
	if (dollar_var(data, src, res, len_buf))
		return ;
	if (!char_append(res, len_buf, *(*src)))
		malloc_failed(data);
	(*src)++;
}

static bool	is_in_heredoc_delim(char *cur, char *line_start)
{
	char	*p;

	p = cur;
	while (p > line_start && !is_space(*(p - 1))
		&& !is_operator(*(p - 1)))
		--p;
	while (p > line_start && is_space(*(p - 1)))
		--p;
	if (p - line_start >= 2 && *(p - 1) == '<' && *(p - 2) == '<')
		return (true);
	if (p - line_start >= 3 && *(p - 1) == '-' && *(p - 2) == '<'
		&& *(p - 3) == '<')
		return (true);
	return (false);
}

int	check_quote_dollars(char **res, int *len_buf, char **src, t_data *data)
{
	if (is_in_heredoc_delim(*src, data->line))
	{
		if (!char_append(res, len_buf, *(*src)))
			malloc_failed(data);
		(*src)++;
		return (1);
	}
	if (is_quoted((*src)[1]))
	{
		(*src)++;
		return (1);
	}
	if (ft_isdigit((*src)[1]))
	{
		(*src) += 2;
		return (1);
	}
	return (0);
}
