/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_op_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:10:46 by mlavry            #+#    #+#             */
/*   Updated: 2025/06/26 21:09:41 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	is_same_op_sequence(const char *s)
{
	char	op;

	if (!s || !*s)
		return (false);
	op = s[0];
	if (!is_operator(op))
		return (false);
	while (*s)
	{
		if (*s != op)
			return (false);
		s++;
	}
	return (true);
}

static void	ft_putnchar_fd(char c, size_t n, int fd)
{
	while (n--)
		ft_putchar_fd(c, fd);
}

static bool	print_op_error(char op, size_t extra, size_t limit)
{
	size_t	print;

	print = extra;
	if (print > limit)
		print = limit;
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putnchar_fd(op, print, 2);
	ft_putstr_fd("'\n", 2);
	g_exit_status = 2;
	return (false);
}

bool	check_arg_op_syntax(t_token *tok)
{
	size_t	len;
	char	op;
	size_t	limit;

	limit = 0;
	if (tok->type != ARG && tok->type != CMD)
		return (true);
	if (!is_same_op_sequence(tok->str))
		return (true);
	len = ft_strlen(tok->str);
	op = tok->str[0];
	if (op == '|')
		limit = 1;
	if (op == '>' || op == '<')
		limit = 2;
	if (limit && len > limit)
		return (print_op_error(op, len - limit, limit));
	return (true);
}
