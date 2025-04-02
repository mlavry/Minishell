/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_start.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <taaikiazerolier@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:02:57 by mlavry            #+#    #+#             */
/*   Updated: 2025/04/02 21:25:33 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	parse_line(t_data *data, char *line)
{
	if (open_quote(data, line))//return (1) en cas d'erreur
	{
		free(line);
		return (false);
	}
	return (true);
}
