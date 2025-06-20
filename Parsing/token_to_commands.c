/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:28:02 by mlavry            #+#    #+#             */
/*   Updated: 2025/06/19 02:40:07 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_append(t_token **tokens, t_cmd **cur)
{
	if (!cur || !*cur)
		return (0);
 	if ((*tokens)->type == APPEND && (!(*tokens)->prev
			|| !(*tokens)->next || (*tokens)->next->type != ARG))
	{
		ft_putstr_fd("shel: syntax error near unexpected token `newline'\n", 2);
		g_exit_status = 2;
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

char	*heredoc_tmp(void)
{
	static int	i = 0;
	char		*num;
	char		*filename;

	num = ft_itoa(i++);
	filename = ft_strjoin("/tmp/heredoc_%d.tmp", num);
	free(num);
	return (filename);
}

/* int	write_heredoc(char *delimiter, int tmp_fd)
{
	char	*line;
	char	*newline;

	while (1)
	{
		reset_signals_to_default();
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
			break ;
		}
		write(tmp_fd, line, ft_strlen(line));
		write(tmp_fd, "\n", 1);
		free(line);
	}
	return (1);
} */

int write_heredoc(char *delimiter, int tmp_fd)
{
    char               *line;
    char               *newline;
    struct sigaction    old_int;
    int                 saved_status = g_exit_status;
	bool				eof = false;

	disable_echoctl();
    hd_set_signals(&old_int);
    g_exit_status = 0;
    while (1)
    {
        write(STDOUT_FILENO, "> ", 2);
        line = get_next_line(STDIN_FILENO);
        if (!line)
		{
			eof = true;
            break ;
		}
        if (g_exit_status == 130)
        {
            free(line);
            break;
        }
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
	enable_echoctl();
    hd_restore_signals(&old_int);
	if (eof && g_exit_status != 130)
	{
		printf("\n");
		printf("minishell: warning: here-document delimited by end-of-file "
			"(wanted `%s')\n", delimiter);
	}
    if (g_exit_status != 130)
        g_exit_status = saved_status;
    return (g_exit_status == 130 ? -1 : 0);
}

int	handle_heredoc(t_token **tokens, t_cmd *cur)
{
	char	*delimiter;
	char	*tmp_filename;
	int		tmp_fd;

	delimiter = (*tokens)->next->str;
	tmp_filename = heredoc_tmp();
	tmp_fd = open(tmp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (tmp_fd == -1)
		return (perror("open tmp"), 0);
	if (!tokens || !*tokens || !(*tokens)->next)
		return (0);
	if (write_heredoc(delimiter, tmp_fd) == -1)
	{
		close(tmp_fd);
		unlink(tmp_filename);
		g_exit_status = 130;
		return (0);
	}
	if (cur->fd_in != STDIN_FILENO)
		close(cur->fd_in);
	cur->fd_in = open(tmp_filename, O_RDONLY);
	if (cur->fd_in == -1)
		return (perror("open heredoc read"), 0);
	free(tmp_filename);
	return (1);
}

/* int	handle_heredoc(t_token **tokens, t_cmd *cur)
{
	char	*delimiter;
	char	*tmp_filename;
	int		tmp_fd;

	delimiter = (*tokens)->next->str;
	tmp_filename = heredoc_tmp();
	tmp_fd = open(tmp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (tmp_fd == -1)
		return (perror("open tmp"), 0);
	if (!tokens || !*tokens || !(*tokens)->next)
		return (0);
	write_heredoc(delimiter, tmp_fd);
	close(tmp_fd);
	if (cur->fd_in != STDIN_FILENO)
		close(cur->fd_in);
	cur->fd_in = open(tmp_filename, O_RDONLY);
	unlink(tmp_filename);
	if (cur->fd_in == -1)
		return (perror("open heredoc read"), 0);
	free(tmp_filename);
	return (1);
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
        		g_exit_status = 2;
        		return false;
    		}
            // Si le token précédent est une redirection, c'est une erreur
            if (tokens->prev && (tokens->prev->type == OUTPUT || tokens->prev->type == HEREDOC || tokens->prev->type == APPEND || tokens->prev->type == INPUT))
            {
                printf("minishell: syntax error near unexpected token `%s'\n", tokens->str);
                g_exit_status = 2;
                return false;
            }
        }

        // Vérifie si le token est une redirection sans fichier suivant
        if ((tokens->type == OUTPUT || tokens->type == APPEND || tokens->type == INPUT) && (!tokens->next || tokens->next->type != ARG))
        {
            printf("minishell: syntax error near unexpected token `%s'\n", tokens->next ? tokens->next->str : "newline");
            g_exit_status = 2;
            return false;
        }

        tokens = tokens->next;
    }
    return true;
} */

/* 
bool	handle_redirect_after_pipe(t_token **tokens, t_cmd **cur)
{
	t_token *tok = *tokens;

	// Vérifie si on est bien sur un token de redirection
	if (!tok || !(tok->type == OUTPUT || tok->type == APPEND || tok->type == INPUT || tok->type == HEREDOC))
		return (false);

	t_cmd *cmd = *cur;

	// On gère chaque type de redirection
	if (tok->type == OUTPUT)
		return handle_output(tokens, &cmd);
	else if (tok->type == APPEND)
		return handle_append(tokens, &cmd);
	else if (tok->type == INPUT)
		return handle_input(tokens, &cmd);
	else if (tok->type == HEREDOC)
		return handle_heredoc_type(tok, tokens, cmd);

	return false;
} */


static bool	is_type_token(t_token **tokens, t_cmd **head, t_cmd **cur)
{
	t_token	*tok;

	tok = *tokens;
	if (!tok)
		return (false);
	/* if (tok->type == HEREDOC)
		return (handle_heredoc_type(tok, tokens, *cur));
	if (tok->type == ARG && handle_redirectarg_type(tok, tokens))
		return (true);
	if (tok->type == CMD)
		return (handle_cmd_type(tok, head, cur, tokens));
	if (tok->type == ARG)
		return (handle_arg_type(tok, *cur, tokens));
	if (tok->type == OUTPUT)
		return (handle_output(tokens, cur));
	if (tok->type == INPUT)
		return (handle_input(tokens, cur));
	if (tok->type == PIPE)
		return (handle_pipe(tokens, cur));
	if (tok->type == APPEND)
		return (handle_append(tokens, cur));
 */

	if (tok->type == HEREDOC)
    	return (handle_heredoc_type(tok, tokens, *cur));
	else if (tok->type == OUTPUT)
   	 	return (handle_output(tokens, cur));
	else if (tok->type == APPEND)
    	return (handle_append(tokens, cur));
	else if (tok->type == INPUT)
   	 	return (handle_input(tokens, cur));
	else if (tok->type == PIPE)
    	return (handle_pipe(tokens, cur));
 	else if (tok->type == ARG && handle_redirectarg_type(tok, tokens))
    	return (true); 
	else if (tok->type == CMD)
    	return (handle_cmd_type(tok, head, cur, tokens));	
	else if (tok->type == ARG)
   	 return (handle_arg_type(tok, *cur, tokens));

	return (true);
}



t_cmd	*tokens_to_commands(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*cur;

	head = NULL;
	cur = NULL;

	if ((tokens->type == PIPE && (!tokens->next || tokens->next->type == PIPE
				|| tokens->next->type == OUTPUT)) || (tokens->type == OUTPUT
			&& (!tokens->next || tokens->next->type != CMD)))
	{
		printf("shell: syntax error near unexpected token\n");
		return (free_cmd(&head), NULL);
	}
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
	g_exit_status = 0;
	while (tokens)
	{
		if (g_exit_status == 130)
			break ;
		if (!is_type_token (&tokens, &head, &cur))
		{
			free_cmd(&head);
			return (NULL);
		}
	}
	return (head);
}

/*  void print_cmds(t_cmd *c)
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
}  */
