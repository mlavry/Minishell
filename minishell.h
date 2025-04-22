/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:37:28 by mlavry            #+#    #+#             */
/*   Updated: 2025/04/22 19:29:13 by mlavry           ###   ########.fr       */
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
# include <term.h>
# include <stdbool.h>

# define INPUT 1 //"<"
# define HEREDOC 2 //"<<"
# define OUTPUT 3 //">"
# define APPEND 4 //">>"
# define PIPE 5 //"|"
# define CMD 6 //"cmd"
# define ARG 7 //"arg"

typedef struct	s_token
{
	char			*str;
	int				type;
	bool			sq;
	bool			dq;
	struct s_token	*next;
}	t_token;

typedef struct	s_env
{
	char				*name;
	char				*value;
	struct s_env		*next;
}	t_env;

typedef struct	s_data
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

//------------------------Make_env---------------------
void	parse_env(char **envp, t_data *env_list);
char	*getenvp(t_env *list, char *name);

//------------------------Utils---------------------
int		ft_strcmp(char *s1, char *s2);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strcat(char *dest, char *src);

#endif
