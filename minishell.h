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
# define PROMPT "minishell:~$ "

extern int	g_exit ;

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

//structure pour les pipes 
/* typedef struct s_pipex
{
	char			**args;
	int				pipe_in;
	int				pipe_out;
	struct s_pipex	*next;
}	t_pipex; */

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

char	*getenvp(t_env *list, char *name);
void	add_env_var(t_env **env_list, char *name, char *value);
void	update_env_var(t_env **env_list, char *name, char *value);
void	parse_env(char **envp, t_env **list);
void	swap_env(t_env *a, t_env *b);
void	sort_env(t_env **env_list);
void	emptyenv(t_env **env_list);
char	**convert_env(t_env *env_list);

char	*get_absolute_path(char *cmd);
char	*find_cmd_path(char *cmd);
char	*getpath(char *cmd);

void	exec_extern_command(char **args, t_env *env_list);
void	executecommand(t_env *list, char *line, t_cmd *cmd);
void	execshell(t_env **env_list);
t_env	*find_env_var(t_env *env_list, char *name);

int		isbuiltin(t_cmd *cmd, t_env *env_list, char **args);
void	builtin_env( t_env *env_list);
void	builtin_cd(t_env **env_list, char *newpath);
void	builtin_pwd(t_cmd *cmd);
void	builtin_echo(t_cmd *cmd, t_env *env_list);
void	builtin_exit(t_cmd *cmd);
void	builtin_unset(t_env **env_list, char **args);

int		validate_export_name(char *name);
char	*extract_name(char *arg);
char	*extract_value(char *arg);
t_env	*copyenvlist(t_env *env_list);
void	built_export(t_env *env_list);
void	builtin_export(t_env **env_list, char **args);

#endif