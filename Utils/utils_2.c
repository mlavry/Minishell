/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:46:33 by mlavry            #+#    #+#             */
/*   Updated: 2025/06/17 22:49:07 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	is_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

/* int	big_heredoc(char *str, int i)
{
	if (ft_strcmp(&str[i], "<<<<") == 0)
	{
		printf("bash: syntax error near unexpected token `<'\n");
		return (1);
	}
	else if (ft_strcmp(&str[i], "<<<<<") == 0)
	{
		printf("bash: syntax error near unexpected token `<<'\n");
		return (1);
	}
	return (0);
}

int	is_multiple_heredoc(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (big_heredoc(str, i))
			return (1);
		if (ft_strcmp(&str[i], "<") == 0 || ft_strcmp(&str[i], "<<") == 0
			|| ft_strcmp(&str[i], "<<<") == 0)
		{
			printf("bash: syntax error near unexpected token `newline'\n");
			return (1);
		}
		else
		{
			while (str[i] == '<')
			{
				printf("bash: syntax error near unexpected token `<<<'\n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	is_multiple_append(char *str)
{
	while (*str)
	{
		if (ft_strcmp(str, ">>>") == 0)
		{
			printf("bash: syntax error near unexpected token `>'\n");
			return (1);
		}
		else if (ft_strcmp(str, ">") == 0 || ft_strcmp(str, ">>") == 0)
		{
			printf("bash: syntax error near unexpected token `newline'\n");
			return (1);
		}
		else
		{
			while (*str == '>')
			{
				printf("bash: syntax error near unexpected token `>>'\n");
				return (1);
			}
		}
		str++;
	}
	return (0);
} */
