/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_commands_type.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:34:37 by aboutale          #+#    #+#             */
/*   Updated: 2025/06/25 18:39:02 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/* 
bool	handle_heredoc_type(t_token *t, t_token **tok, t_cmd **cur)
{
	if (!t->next || t->next->type != ARG)
	{
		ft_putstr_fd("shel: syntax error near unexpected token `newline'\n", 2);
		g_exit_status = 2;
		return (false);
	}
	if (!cur)
    {
        t_cmd *new_cmd = create_new_cmd();
        if (!new_cmd)
            return (false);
        cur = &new_cmd;
    }

	if (!handle_heredoc(tok, *cur))
		return (false);
	*tok = (*tok)->next->next;
	return (true);
}   */

// Dans ./Parsing/handle_commands_type.c
bool	handle_heredoc_type(t_data *data, t_token *t, t_token **tok, t_cmd **cur)
{
	if (!t->next || t->next->type != ARG)
	{
		// ... erreur
		return (false);
	}

    // Si `*cur` est NULL, cela signifie qu'aucune commande n'a encore été créée.
    // C'est le cas pour `<< E | ls`. On doit créer la première commande.
	if (*cur == NULL)
    {
        *cur = create_new_cmd(); // On modifie le pointeur `cur` de la fonction appelante
        if (!*cur)
            return (false);
        
        // Il faut aussi mettre à jour la tête de liste si elle est vide
        // La logique pour ça doit être dans `tokens_to_commands`
    }

	if (!handle_heredoc(data, tok, *cur)) // On passe *cur (la commande) à handle_heredoc
		return (false);
	
	*tok = (*tok)->next->next; // On avance de 2 tokens (<< et le délimiteur)
	return (true);
}

/* bool	handle_heredoc_type(t_token *t, t_token **tok, t_cmd **cur)
{
    if (!t || !t->next || t->next->type != ARG)
    {
        ft_putstr_fd("shel: syntax error near unexpected token `newline'\n", 2);
        g_exit_status = 2;
        return (false);
    }

    // Si cur == NULL → crée une nouvelle commande vide
    if (!*cur)
    {
        *cur = create_new_cmd();
        if (!*cur)
            return false;
    }

    // Applique le here-doc
    if (!handle_heredoc(tok, *cur))
        return (false);

    // Saute `<<` et le délimiteur
    *tok = (*tok)->next->next;

    // Vérifie si le token suivant est un ARG (ex: "LOL")
    if (*tok && (*tok)->type == ARG)
    {
        char *cmd_name = (*tok)->str;
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(cmd_name, 2);
        ft_putstr_fd(": command not found\n", 2);
        g_exit_status = 127;

        // Ignore ce token
        *tok = (*tok)->next;
    }

    return (true);
} */


bool	handle_cmd_type(t_token *tok, t_cmd **hd, t_cmd **cur, t_token **tokens)
{
	bool	ok;

	ok = handle_cmd(hd, cur, tok);
	*tokens = tok->next;
	return (ok);
}

bool	handle_arg_type(t_token *tok, t_cmd *cur, t_token **tokens)
{
	bool	ok;

	ok = handle_arg(cur, tok);
	*tokens = tok->next;
	return (ok);
}

bool	handle_redirectarg_type(t_token *tok, t_token **tokens)
{
	if (tok && tok->prev && tok->prev->type
		&& (tok->prev->type == OUTPUT
			|| tok->prev->type == INPUT
			|| tok->prev->type == APPEND
			|| tok->prev->type == HEREDOC))
	{
		*tokens = tok->next;
		return (true);
	}
	return (false);
}
