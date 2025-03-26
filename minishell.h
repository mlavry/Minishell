/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:55:21 by mlavry            #+#    #+#             */
/*   Updated: 2025/03/26 18:08:17 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft/libft.h"
# include <sys/types.h>          // Types de données généraux (pid_t, mode_t, etc.)
# include <readline/readline.h>  // Fonctions readline, rl_replace_line, rl_on_new_line, rl_redisplay, etc.
# include <readline/history.h>   // Fonctions add_history, rl_clear_history, etc.
# include <stdio.h>              // printf, perror, etc.
# include <stdlib.h>             // malloc, free, exit, getenv, etc.
# include <unistd.h>             // fork, write, read, close, access, getcwd, chdir, unlink, dup, dup2, pipe, isatty, ttyname, ttyslot (selon les implémentations), execve, etc.
# include <fcntl.h>              // open (et les flags associés)
# include <sys/wait.h>           // wait, waitpid, wait3, wait4
# include <signal.h>             // signal, sigaction, sigemptyset, sigaddset, kill
# include <sys/stat.h>           // stat, lstat, fstat
# include <dirent.h>             // opendir, readdir, closedir
# include <string.h>             // strerror, éventuellement d’autres manipulations de chaînes
# include <sys/ioctl.h>          // ioctl
# include <termios.h>            // tcsetattr, tcgetattr
# include <term.h>               // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

//------------------------First functions---------------------



#endif