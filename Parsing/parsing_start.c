/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_start.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:55:39 by mlavry            #+#    #+#             */
/*   Updated: 2025/06/12 03:46:54 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_token_prev_links(t_token *tokens)
{
	t_token *prev = NULL;
	while (tokens)
	{
		tokens->prev = prev;
		prev = tokens;
		tokens = tokens->next;
	}
}



bool validate_tokens(t_token *tokens, t_data *data)
{
    while (tokens)
    {
        if (tokens->type == OUTPUT || tokens->type == INPUT
            || tokens->type == APPEND || tokens->type == HEREDOC)
        {
            if (!tokens->next || tokens->next->type != ARG)
            {
                ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
                if (!tokens->next)
                    ft_putstr_fd("newline", 2);
                else
                    ft_putstr_fd(tokens->next->str, 2);
                ft_putstr_fd("'\n", 2);
                data->exit_code = 2;
                return false;
            }
        }
        else if (tokens->type == PIPE)
        {
            // PIPE en début ou fin de ligne ?
            if (!tokens->prev || !tokens->next)
            {
                ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
                data->exit_code = 2;
                return false;
            }
            // Optionnel : vérifier que tokens->prev et tokens->next ne sont pas PIPE ou opérateurs
            if (tokens->prev->type == PIPE || tokens->next->type == PIPE)
            {
                ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
                data->exit_code = 2;
                return false;
            }
        }
        tokens = tokens->next;
    }
    return true;
}


bool	parse_line(t_data *data)
{
	if (open_quote(data, data->line))
	{
		free(data->line);
		return (false);
	}
	replace_dollars(data);
	if (!tokenize(data))
	{
		free(data->line);
		return (false);
	}
	set_token_prev_links(data->token);
	if (!validate_tokens(data->token, data))
	{
   	 	free(data->line);
   		 free_token(&data->token);
   	 	return false;
	}

	data->cmd = tokens_to_commands(data->token, data);
	if (!(data->cmd))
	{
		free(data->line);
		return (false);
	}
	//print_cmds(data->cmd);
	return (true);
}
