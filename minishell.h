/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:37:28 by mlavry            #+#    #+#             */
/*   Updated: 2025/06/27 01:06:45 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft/libft.h"
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <stdbool.h>
# include <limits.h>
# include "Gnl/get_next_line.h"

# define INPUT 1
# define HEREDOC 2
# define OUTPUT 3
# define APPEND 4
# define PIPE 5
# define CMD 6
# define ARG 7

extern int	g_exit_status;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_cmd
{
	char			*name;
	char			**args;
	int				fd_in;
	int				fd_out;
	char			*heredoc_file;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_env
{
	char				*name;
	char				*value;
	struct s_env		*next;
}	t_env;

typedef struct s_data
{
	char		*line;
	int			nb_hd;
	int			hd_idx;
	bool		*expand_hd;
	t_env		*env;
	t_token		*token;
	t_cmd		*cmd;
}				t_data;

//------------------------Parsing functions---------------------
bool	parse_line(t_data *data);
int		open_quote(char *line);
int		tokenize(t_data *data);
int		is_quoted(char c);
void	quote_choice(bool *sq, bool *dq, char c);
int		count_tokens(char *line);
char	**line_to_token(t_data *data);
void	mark_commands(t_data *data);
int		add_args(char ***args, char *str);
t_cmd	*tokens_to_commands(t_data *data, t_token *tokens);
bool	handle_heredoc_type(t_data *data, t_token *t,
			t_token **tok, t_cmd **cur);
bool	handle_cmd_type(t_token *tok, t_cmd **hd,
			t_cmd **cur, t_token **tokens);
bool	handle_arg_type(t_token *tok, t_cmd *cur, t_token **tokens);
bool	handle_redirectarg_type(t_token *tok, t_token **tokens);
int		handle_output(t_token **tokens, t_cmd **cur);
int		handle_input(t_token **tokens, t_cmd **cur);
int		handle_pipe(t_data *data, t_token **tokens, t_cmd **cur);
int		handle_heredoc(t_data *data, t_token **tokens, t_cmd *cur);
int		handle_append(t_token **tokens, t_cmd **cur);
int		handle_arg(t_cmd *cur, t_token *token);
int		handle_cmd(t_cmd **head, t_cmd **cur, t_token *tokens);
void	init_data(t_data *data, int argc, char **argv, char **envp);
void	replace_dollars(t_data *data);
char	*check_next(char *line, char *actual_chain, int *pos);
bool	check_arg_op_syntax(t_token *tok);
void	mark_heredoc_quotes(t_data *data);
int		count_heredocs(char *line);
void	check_dollars(t_data *data, char **src, char **res, int *len_buf);
void	replace_dollars_heredocs(t_data *data, char **delim);
char	*handle_dq_joined(char *line, char *old_chain, bool *dq, int *pos);
char	*handle_sq_joined(char *line, char *old_chain, bool *sq, int *pos);
char	*handle_chain_joined(char *line, char *old_chain, int *pos);
char	*extract_chain(char *line, int *pos);
char	*extract_sq(char *line, int *pos, bool *sq);
char	*extract_dq(char *line, int *pos, bool *dq);
int		handle_sq(char *line, char **tokens, bool *sq, int *pos);
void	skip_dup_quotes(char *line, int *pos);
void	handle_operator(char *line, char **temp, int *pos);
int		handle_dq(char *line, char **tokens, bool *dq, int *pos);
void	skip_leading_spaces(char *line, int *pos);
int		handle_unquoted(char *line, char **tokens, int *pos);
int		handle_heredoc(t_data *data, t_token **tokens, t_cmd *cur);
char	*heredoc_tmp(void);
int		write_heredoc(t_data *d, int idx, char *delim, int fd);
int		check_quote_dollars(char **res, int *len_buf, char **src, t_data *data);
void	check_dollars(t_data *data, char **src, char **res, int *len_buf);
void	set_token_prev_links(t_token *tokens);
bool	validate_tokens(t_token *tokens);
void	check_value(t_data *data, t_token *token);

//------------------------Env---------------------
void	parse_env(char **envp, t_data *env_list);
char	*getenvp(t_env *list, char *name);
void	add_env_var(t_data *data, t_env **env_list, char *name, char *value);
void	update_env_var(t_env **env_list, char *name, char *value);
void	swap_env(t_env *a, t_env *b);
void	sort_env(t_env **env_list);
void	emptyenv(t_data *data, t_env **env_list);
char	**convert_env(t_data *data, t_env *env_list);
t_env	*find_env_var(t_env *env_list, char *name);

//------------------------Utils---------------------
int		ft_strcmp(char *s1, char *s2);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strcat(char *dest, char *src);
int		is_operator(char c);
int		is_space(char c);
bool	is_redir(int type);
int		str_append(char **res, int *len_buf, const char *add);
int		char_append(char **res, int *len_buf, char c);
int		ft_isnumeric(const char *str);
int		check_operators(char *line, char **tokens, int *pos);
int		ft_atoi_safe(const char *str, int *out);
int		free_ret(char *ptr);

//------------------------Signals---------------------
void	init_signals_prompt(void);
void	handle_status_and_print(int status);
void	reset_signals_to_default(void);
void	ignore_sigint(void);
void	hd_set_signals(struct sigaction *old_int);
void	hd_restore_signals(const struct sigaction *old_int);
void	disable_echoctl(void);
void	enable_echoctl(void);

//------------------------Free functions---------------------
void	free_tab(char **tokens);
void	free_env(t_env **env);
void	free_token(t_token **token);
void	free_cmd(t_cmd **cmd);
void	free_all(t_data *data, int exit_code, bool exit_or_not);
void	malloc_failed(t_data *data);
void	close_all_fd(void);

//------------------------Exec---------------------
int		isbuiltin(t_data *data);
void	exec_builtin(t_data *data);
void	builtin_env(t_env *env_list, t_data *data);
void	builtin_cd( char *newpath, t_data *data);
void	builtin_pwd(void);
void	builtin_echo(t_data *data);
void	builtin_exit(t_data *data);
void	builtin_unset(t_env **env_list, t_cmd *cmd);
void	existing_value(t_data *data, t_env **env_list, char *name, char *value);
int		validate_export_name(char *name);
char	*extract_name(char *arg);
char	*extract_value(char *arg);
t_env	*copyenvlist(t_data *data, t_env *env_list);
void	built_export(t_data *data, t_env *env_list);
void	built_export2(t_data *data, t_env **env_list, char **args);
int		loop(t_env *current, char *new_value, char *var_name);
void	builtin_export(t_data *data, t_env **env_list, t_cmd *cmd);
void	updatepwd(t_data *data, t_env **env_list, char *oldpath);
char	*getpath(char *cmd, t_data *data);
void	execshell(t_data *data, t_env **env_list);
void	executecommand(t_data *data);
void	exec_extern_command(char **args, t_env *env_list, t_data *data);
void	exec_pipe(t_cmd *cmd, t_data *data);
bool	is_a_directory(char *path, char **args);
void	built_path(char *newpath, t_data *data);
void	handle_command_error(char *cmd, char *msg, int exit_code, t_data *data);
t_cmd	*create_new_cmd(void);
bool	is_redirection(int type);
int		write_heredoc(t_data *data, int hd_idx, char *delimiter, int tmp_fd);
void	print_error(char *cmd, char *msg);
int		check_cd_errors(char *newpath);
void	launch_extern_command(char **args, t_env *env, t_data *data);
void	setup_outandin(t_cmd *cmd, int prev_fd, int *pipe_fd);
void	exec_command(t_cmd *cmd, t_data *data);
void	parent(t_cmd *current_cmd, int *prev_fd, int *pipe_fd);

#endif
