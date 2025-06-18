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

static bool is_shell_delim(char c)
{
    return (c == '|' || c == '&' || c == ';' ||
            c == '(' || c == ')' || c == '<' || c == '>');
}

static bool  is_in_heredoc_delim(char *cur, char *line_start)
{
    char *p = cur;

    while (p > line_start &&
           !is_space(*(p - 1)) &&
           !is_shell_delim(*(p - 1)))
        --p;
    while (p > line_start && is_space(*(p - 1)))
        --p;
    if (p - line_start >= 2 &&
        *(p - 1) == '<' && *(p - 2) == '<')
        return true;

    if (p - line_start >= 3 &&
        *(p - 1) == '-' &&
        *(p - 2) == '<' && *(p - 3) == '<')
        return true;
    return false;
}

/* retourne 1 si on NE doit PAS expander  */
int  check_quote_dollars(char **res, int *len_buf, char **src, t_data *data)
{
    /* a) le $ est dans le mot-délimiteur here-doc -------------- */
    if (is_in_heredoc_delim(*src, data->line))
    {
		if (!char_append(res, len_buf, *(*src)))
			malloc_failed(data);
        (*src)++;          /* on garde le caractère tel quel      */
        return 1;
    }

    /* b) juste après un guillemet ------------------------------ */
    if (is_quoted((*src)[1]))
    {
        (*src)++;
        return 1;
    }

    /* c) cas $<digit> ----------------------------------------- */
    if (ft_isdigit((*src)[1]))
    {
        (*src) += 2;
        return 1;
    }
    return 0;              /* expansion normale sinon             */
}

void	replace_dollars(t_data *data)
{
	char	*src;
	char	*res;
	int		len_buf;
	bool	sq;
	bool	dq;

	src = data->line;
	res = ft_strdup("");
	if (!res)
		malloc_failed(data);
	len_buf = 0;
	sq = false;
	dq = false;
	while (*src)
	{
		quote_choice(&sq, &dq, *src);
		if (*src == '$' && !dq && !sq)
		{
			if (check_quote_dollars(&res, &len_buf, &src, data))
				continue ;
		}
		if (*src == '$' && !sq)
		{
			check_dollars(data, &src, &res, &len_buf);
			continue ;
		}
		if (!char_append(&res, &len_buf, *src))
			malloc_failed(data);
		src++;
	}
	free(data->line);
	data->line = res;
}
