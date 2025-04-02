/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <taaikiazerolier@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:55:21 by mlavry            #+#    #+#             */
/*   Updated: 2025/04/02 21:05:28 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define CODE_ERROR 2
# define CODE_

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

typedef struct	s_list_str
{
	char				*str;
	struct s_list_str	*next;
	struct s_list_str	*prev;
}						t_lis_str;

typedef struct	s_data
{
	t_lis_str	*env;
	int			exit_code;
}				t_data;

//------------------------Parsing functions---------------------
bool	parse_line(t_data *data, char *line);
int		open_quote(t_data *data, char *line);

#endif
