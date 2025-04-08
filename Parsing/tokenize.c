/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <taaikiazerolier@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:41:00 by mlavry            #+#    #+#             */
/*   Updated: 2025/04/08 21:03:16 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	tokenize(t_data *data, char *line)
{
	char	**token;
	int		i;

	i = 0;
	token = ft_split(line, ' ');
	if (!token)
	{
		data->exit_code = 2;
		return (0);
	}
	
	/* while (token[i])
	{
		ft_printf("Token %d : %s\n",i , token[i]);
		i++;
	} */
	return (1);
}

void	parse_token(t_token **token_list, char **tokens)
{
	t_token		*new_token = malloc(sizeof(t_token));

	
}
