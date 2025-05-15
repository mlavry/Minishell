/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:25:55 by mlavry            #+#    #+#             */
/*   Updated: 2025/05/15 21:27:12 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	dollar_exit(t_data *data, char **src, char **res, int *len_buf)
{
	char	*nbr;

	nbr = ft_itoa(data->exit_code);
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

void	check_dollars(t_data *data, char **src, char **res, int *len_buf)
{
	if ((*src)[1] == '?')
	{
		if (!dollar_exit(data, src, res, len_buf))
			malloc_failed(data);
		return ;
	}
	if (!char_append(res, len_buf, *(*src)))
		malloc_failed(data);
	(*src)++;
}

void	replace_dollars(t_data *data)
{
	char	*src;
	char	*res;
	int		len_buf;
	bool	sq;
	bool	dq;

	src = data->line;
	res = NULL;
	len_buf = 0;
	sq = false;
	dq = false;
	while (*src)
	{
		quote_choice(&sq, &dq, *src);
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

/*if (data.line[0] == '$')
		{
			if (data.line[1] == '?')
			{
				printf("%d: command not found\n", data.exit_code);
				data.exit_code = 127;
			}
			char *value = getenvp(data.env, data.line + 1);
			if (value)
				printf("bash : %s : command not found\n", value);
			if (value && access(value, X_OK))
				printf("bash : %s no such file or directory\n", value);
		}
*/