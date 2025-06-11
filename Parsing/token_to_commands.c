/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:28:02 by mlavry            #+#    #+#             */
/*   Updated: 2025/05/29 15:19:29 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_cmd(t_cmd **head, t_cmd **cur, t_token *tokens)
{
	t_cmd	*new;

	new = ft_calloc (1, sizeof(t_cmd));
	if (!new)
		return (0);
	new->name = ft_strdup(tokens->str);
	if (!new->name)
	{
		free(new);
		return (0);
	}
	new->fd_in = STDIN_FILENO;
	new->fd_out = STDOUT_FILENO;
	if (!add_args(&new->args, new->name))
	{
		free(new->name);
		free(new);
		return (0);
	}
	if (!(*head))
		(*head) = new;
	else
		(*cur)->next = new;
	(*cur) = new;
	return (1);
}

int	handle_arg(t_cmd *cur, t_token *token)
{
	if (!cur)
		return (0);
	if (!add_args(&cur->args, token->str))
		return (0);
	return (1);
}

int	handle_pipe(t_token **tokens, t_cmd **cur)
{
	if (!cur || !*cur)
		return (0);
	if ((*tokens)->type == PIPE && (!(*tokens)->next))
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (0);
	}
	*tokens = (*tokens)->next;
	if (!cur || !*cur)
		return (0);
	return (1);
}


int	handle_output(t_token **tokens, t_cmd **cur, t_data *data)
{
	if (!cur || !*cur)
		return (0);
	if ((*tokens)->type == OUTPUT
		&& (!(*tokens)->next || (*tokens)->next->type != ARG))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
		data->exit_code = 2;
		return (0);
	}
	if ((*tokens)->next && (*tokens)->next->type == ARG)
	{
		if ((*cur)->fd_out != STDOUT_FILENO && (*cur)->fd_out != -1)
			close((*cur)->fd_out);
		(*cur)->fd_out = open((*tokens)->next->str,
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if ((*cur)->fd_out < 0)
		{
			printf("%s: No such file or directory\n", (*tokens)->next->str);
			return (0);
		}
		*tokens = (*tokens)->next;
	}
	return (1);
}

int	handle_input(t_token **tokens, t_cmd **cur, t_data *data)
{
	if (!cur || !*cur)
		return (0);
	if (tokens && ((*tokens)->type == INPUT)
		&& (!(*tokens)->next || (*tokens)->next->type != ARG))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
		data->exit_code = 2;
		return (0);
	}
	if ((*tokens)->next && (*tokens)->next->type == ARG)
	{
		if ((*cur)->fd_in != STDIN_FILENO)
			close((*cur)->fd_in);
		(*cur)->fd_in = open((*tokens)->next->str, O_RDONLY);
		if ((*cur)->fd_in < 0)
		{
			printf("%s: No such file or directory\n", (*tokens)->next->str);
			return (0);
		}
		*tokens = (*tokens)->next;
	}
	return (1);
}


int	handle_append(t_token **tokens, t_cmd **cur, t_data *data)
{
	if (!cur || !*cur)
		return (0);
	if ((*tokens)->type == APPEND && (!(*tokens)->prev
			|| !(*tokens)->next || (*tokens)->next->type != ARG))
	{
    	ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
		data->exit_code = 2;
		return (0);
	}
	if ((*tokens) && (*tokens)->type == APPEND
		&& (*tokens)->next && (*tokens)->next->type == ARG)
	{
		if ((*cur)->fd_out != STDOUT_FILENO && (*cur)->fd_out != -1)
			close((*cur)->fd_out);
		(*cur)->fd_out = open((*tokens)->next->str,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if ((*cur)->fd_out < 0)
		{
			perror("open");
			return (0);
		}
		*tokens = (*tokens)->next->next;
	}
	return (1);
}

int handle_heredoc(t_token **tokens, t_cmd *cur, t_data *data)
{
	(void)data;
	if (!tokens || !*tokens || !(*tokens)->next)
		return 0;

	char *delimiter = (*tokens)->next->str;
	char *line;
	char *newline;
	char *rand_str = ft_itoa(rand());
	char *tmp_filename = ft_strjoin("/tmp/heredoc_%d.tmp", rand_str);
	free(rand_str);
	int tmp_fd = open(tmp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (tmp_fd == -1)
		return perror("open tmp"), 0;

	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line)
			break ;
		newline = ft_strchr(line, '\n');
		if (newline)
			*newline = '\0';
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
		}
		write(tmp_fd, line, ft_strlen(line));
		write(tmp_fd, "\n", 1);
		free(line);
	}
	close(tmp_fd);
	if (cur->fd_in != STDIN_FILENO)
		close(cur->fd_in);
	cur->fd_in = open(tmp_filename, O_RDONLY);
	if (cur->fd_in == -1)
		return perror("open heredoc read"), 0;
	return 1;
}


/* 
int	handle_heredoc(t_token **tokens, t_cmd **cur, t_data *data)
{
	char	*delimiter;
	int		pipefd[2];
	char	*line;

	if (!cur || !*cur || !tokens || !*tokens) // <-- AJOUT POUR ÉVITER LE CRASH
		return (0);
	if ((*tokens)->type == HEREDOC
		&& ( !(*tokens)->prev || !(*tokens)->next || (*tokens)->next->type != ARG))
	{
		data->exit_code = 2;
		return (0);
	}
	delimiter = (*tokens)->next->str;
//	if ((*cur)->fd_in != STDIN_FILENO)
	//	close((*cur)->fd_in);
	if (pipe(pipefd) == -1)
	{
    	perror("pipe");
    	return 0;
	}
	while(1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line || ft_strncmp(line, delimiter, ft_strlen(delimiter)+1) == 0 
			 || ft_strcmp(line, ft_strcat(ft_strdup(delimiter), "\n")) == 0 )
		{
			free(line);
			break;
		}
		write(pipefd[1], line, ft_strlen(line));
		free(line);
	}
	close(pipefd[1]);
	(*cur)->fd_in = pipefd[0];
	*tokens = (*tokens)->next;
	return (1);
} */




bool is_type_token(t_token **tokens, t_cmd **head, t_cmd **cur, t_data *data)
{
	t_token *tok = *tokens;

	if (!tok)
		return false;
	if (tok->type == ARG)
	{
		if (tok->prev &&
			(tok->prev->type == OUTPUT ||
			tok->prev->type == INPUT ||
			tok->prev->type == APPEND ||
			tok->prev->type == HEREDOC))
		{
			*tokens = tok->next;
			return true;
		}
	}
	if (tok->type == CMD)
	{
		bool ok = handle_cmd(head, cur, tok);
		*tokens = tok->next;
		return ok;
	}
	if (tok->type == ARG)
	{
		bool ok = handle_arg(*cur, tok);
		*tokens = tok->next;
		return ok;
	}
	if (tok->type == OUTPUT)
		return handle_output(tokens, cur, data);
	if (tok->type == INPUT)
		return handle_input(tokens, cur, data);
	if (tok->type == PIPE)
		return handle_pipe(tokens, cur);
	if (tok->type == APPEND)
		return handle_append(tokens, cur, data);

	// ✅ Gérer plusieurs heredocs consécutifs
	if (tok->type == HEREDOC)
	{
		if (tok->type == HEREDOC && (!tok->next || tok->next->type != ARG))
		{
    		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
    		data->exit_code = 2;
    		return false; // ✨ très important
		}

		if (!handle_heredoc(tokens, *cur, data))
			return false;
		*tokens = (*tokens)->next->next; // HEREDOC + ARG
		return true;
	}
	return true;
}






/* 
bool	is_type_token(t_token **tokens, t_cmd **head, t_cmd **cur, t_data *data)
{
	if ((*tokens)->type == CMD)
		return (handle_cmd(head, cur, *tokens));
	if ((*tokens)->type == ARG)
		return (handle_arg(*cur, *tokens));
	if ((*tokens)->type == OUTPUT)
		return (handle_output(tokens, cur, data));
	if ((*tokens)->type == INPUT)
		return (handle_input(tokens, cur, data));
	if ((*tokens)->type == PIPE)
		return (handle_pipe(tokens,cur));
 	while ((*tokens)->type == HEREDOC)
	{
       if( !handle_heredoc(tokens, cur, data))
			return false;
   		if (*tokens)
        	*tokens = (*tokens)->next;
		else
			break;
	}
	if ((*tokens)->type == GREAT || (*tokens)->type == DGREAT)
		return(handle_output_redirect(tokens,cur, data));
	if ((*tokens)->type == APPEND)
        return (handle_append(tokens ,cur, data)); 
	return (true);
}  */
/* bool	is_type_token(t_token **tokens, t_cmd **head, t_cmd **cur, t_data *data)
{
	t_token *tok = data->token;
	while (tok)
	{
		if (tok->type == HEREDOC)
		{
			if (!handle_heredoc(&tok, &data->cmd, data))
				break;
		}
		else if (tok->type == GREAT || tok->type == DGREAT)
		{
			if (!handle_output_redirect(&tok, &data->cmd, data))
				break;
		}
		else if (tok->type == CMD)
		{
			handle_cmd(head, cur, *tokens);
			tok = tok->next;
		}
		else if (tok->type == ARG)
		{
			handle_arg(*cur, *tokens);
			tok = tok->next;
		}
		else
			tok = tok->next;
	}
	return true;
} */





/* bool check_token_syntax(t_token *tokens, t_data *data)
{
    while (tokens)
    {
        // Vérifie si le token est un pipe
        if (tokens->type == PIPE)
        {
			 if (!tokens->prev || !tokens->next)
   			 {
        		printf("minishell: syntax error near unexpected token `|'\n");
        		data->exit_code = 2;
        		return false;
    		}
            // Si le token précédent est une redirection, c'est une erreur
            if (tokens->prev && (tokens->prev->type == OUTPUT || tokens->prev->type == HEREDOC || tokens->prev->type == APPEND || tokens->prev->type == INPUT))
            {
                printf("minishell: syntax error near unexpected token `%s'\n", tokens->str);
                data->exit_code = 2;
                return false;
            }
        }

        // Vérifie si le token est une redirection sans fichier suivant
        if ((tokens->type == OUTPUT || tokens->type == APPEND || tokens->type == INPUT) && (!tokens->next || tokens->next->type != ARG))
        {
            printf("minishell: syntax error near unexpected token `%s'\n", tokens->next ? tokens->next->str : "newline");
            data->exit_code = 2;
            return false;
        }

        tokens = tokens->next;
    }
    return true;
} */


t_cmd	*tokens_to_commands(t_token *tokens, t_data *data)
{
	t_cmd	*head;
	t_cmd	*cur;

	head = NULL;
	cur = NULL;
	if (tokens && (tokens->type == OUTPUT || tokens->type == INPUT
			|| tokens->type == APPEND || tokens->type == HEREDOC))
	{
		cur = ft_calloc(1, sizeof(t_cmd));
		if (!cur)
			return (NULL);
		cur->fd_in = STDIN_FILENO;
		cur->fd_out = STDOUT_FILENO;
		cur->name = ft_strdup("");
		head = cur;
	}
	while (tokens)
	{
		if (!is_type_token (&tokens, &head, &cur, data))
		{
			free_cmd(&head);
			return NULL;
		}
	}
	return (head);
}

/* void print_cmds(t_cmd *c)
{
    int idx;
    while (c)
    {
        printf("=== Command: %s ===\n", c->name);
        for (idx = 0; c->args && c->args[idx]; idx++)
            printf("  arg[%d]: %s\n", idx, c->args[idx]);
        printf("  fd_in = %d, fd_out = %d\n", c->fd_in, c->fd_out);
        c = c->next;
    }
} */
