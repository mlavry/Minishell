/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:02:03 by aboutale          #+#    #+#             */
/*   Updated: 2025/03/24 18:02:05 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>

# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# define PROMPT "aboutale@k1r3p1:~$ "



//structure pour l'environnement et le PATH
typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;


//structure pour les commandes 
typedef struct s_cmd
{
	char			*name;
	char			**args;
	int				fd_in;
	int				fd_out;
	struct s_cmd	*next;
}	t_cmd;


//structure pour les pipes et redirections
typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		pipes[2][2];
	char	**paths;
	char	**cmds;
	int		n_commands;
	char	**envp;
}	t_pipex;

void	parse_env(char **envp, t_env **list);
void	ft_pwd(void);
void	executecommand(t_env *list, char *line, char **envp, t_cmd *cmd);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(const char *s, char c);
char	*getenvp(t_env *list, char *name);
void	execute_pipeline(t_env *env_list, char *line);
void	free_split(char **split_paths);
int		isbuiltin(t_cmd *cmd, t_env *env_list);
void	builtin_env( t_env *env_list);
void	builtin_cd(char *newpath);
void	builtin_pwd(t_cmd *cmd);
void	builtin_echo(t_cmd *cmd, t_env *env_list);
void	builtin_exit(t_cmd *cmd);
void	builtin_export(t_env *env_list, t_cmd *cmd);

#endif