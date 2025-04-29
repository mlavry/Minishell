/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:37:28 by mlavry            #+#    #+#             */
/*   Updated: 2025/04/29 19:49:19 by mlavry           ###   ########.fr       */
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
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <stdbool.h>

# define INPUT 1 //"<"
# define HEREDOC 2 //"<<"
# define OUTPUT 3 //">"
# define APPEND 4 //">>"
# define PIPE 5 //"|"
# define CMD 6 //"cmd"
# define ARG 7 //"arg"

typedef struct s_token
{
	char			*str;
	int				type;
	bool			sq;
	bool			dq;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_cmd
{
	char			*name;
	char			**args;
	int				fd_in;
	int				fd_out;
	int				g_exit;
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
	t_env		*env;
	t_token		*token;
	int			exit_code;
}				t_data;

//------------------------Parsing functions---------------------
bool	parse_line(t_data *data, char *line);
int		open_quote(t_data *data, char *line);
int		tokenize(t_data *data, char *line);
int		is_quoted(char c);
void	stock_and_delete_quote(t_token *token);
void	quote_choice(bool *sq, bool *dq, char c);
int		count_tokens(char *line);
char	**line_to_token(char *line);

//------------------------Env---------------------
void	parse_env(char **envp, t_data *env_list);
char	*getenvp(t_env *list, char *name);
void	add_env_var(t_env **env_list, char *name, char *value);
void	update_env_var(t_env **env_list, char *name, char *value);
void	swap_env(t_env *a, t_env *b);
void	sort_env(t_env **env_list);
void	emptyenv(t_env **env_list);
char	**convert_env(t_env *env_list);
t_env	*find_env_var(t_env *env_list, char *name);

//------------------------Utils---------------------
int		ft_strcmp(char *s1, char *s2);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strcat(char *dest, char *src);
int		is_operator(char c);
int		is_space(char c);

//------------------------Free functions---------------------
void	free_tab(char **tokens);
void	free_env_list(t_env *env_list);

//------------------------Exec---------------------
int		isbuiltin(t_cmd *cmd, t_env *env_list);
void	builtin_env( t_env *env_list);
void	builtin_cd(t_env **env_list, char *newpath);
void	builtin_pwd(t_cmd *cmd);
void	builtin_echo(t_cmd *cmd, t_env *env_list);
void	builtin_exit(t_cmd *cmd,t_env *env_list);
void	builtin_unset(t_env **env_list, t_cmd *cmd);
int		validate_export_name(char *name);
char	*extract_name(char *arg);
char	*extract_value(char *arg);
t_env	*copyenvlist(t_env *env_list);
void	built_export(t_env *env_list);
void	builtin_export(t_env **env_list, t_cmd *cmd);
void	updatepwd(t_env **env_list, char *oldpath);
char	*getpath(char *cmd, t_cmd *cmds);


#endif
