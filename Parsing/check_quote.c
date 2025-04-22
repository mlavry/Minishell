/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 21:21:34 by mlavry            #+#    #+#             */
/*   Updated: 2025/04/22 22:28:39 by mlavry           ###   ########.fr       */
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

int	open_quote(t_data *data, char *line)//I think she work
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
		data->exit_code = 2;
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

void	stock_and_delete_quote(t_token *token) //appeler une fois que les token sont deja initialiser et faire attention a ce que dq et sq soit bien initialiser
{
	int		len;
	char	*tmp;

	len = (int)ft_strlen(token->str);
	if (!token || !token->str || len < 2)
		return ;
	if (token->str[0] == '\'' && token->str[len - 1] == '\'')
	{
		token->sq = true;
		tmp = ft_substr(token->str, 1, len - 2);
		if (!tmp)
			return ;
		free(token->str);
		token->str = tmp;
	}
	else if (token->str[0] == '"' && token->str[len - 1] == '"')
	{
		token->dq = true;
		tmp = ft_substr(token->str, 1, len - 2);
		if (!tmp)
			return ;
		free(token->str);
		token->str = tmp;
	}
}
