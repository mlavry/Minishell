/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <taaikiazerolier@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:37:28 by mlavry            #+#    #+#             */
/*   Updated: 2025/04/07 20:47:47 by mlavry           ###   ########.fr       */
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

typedef struct	s_env
{
	char				*name;
	char				*value;
	struct s_env		*next;
	struct s_env		*prev;
}	t_env;

typedef struct	s_data
{
	t_env		*env;
	int			exit_code;
}				t_data;

//------------------------Parsing functions---------------------
bool	parse_line(t_data *data, char *line);
int		open_quote(t_data *data, char *line);

//------------------------Make_env---------------------
void	parse_env(char **envp, t_data *env_list);
char	*getenvp(t_env *list, char *name);

//------------------------Utils---------------------
int		ft_strcmp(char *s1, char *s2);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strcat(char *dest, char *src);

#endif
