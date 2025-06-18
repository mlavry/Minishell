/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_hd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 00:50:33 by mlavry            #+#    #+#             */
/*   Updated: 2025/06/18 21:00:20 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void  sigint_hd(int signo)
{
    (void)signo;
    g_exit_status = 130;
    write(STDOUT_FILENO, "^C\n", 3);
}

void    hd_set_signals(struct sigaction *old_int)
{
    struct sigaction sa;

    sa.sa_handler = sigint_hd;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags  = 0;
    sigaction(SIGINT, &sa, old_int);
	signal(SIGQUIT, SIG_IGN);
}

void    hd_restore_signals(const struct sigaction *old_int)
{
    sigaction(SIGINT,  old_int,  NULL);
}

void    disable_echoctl(void)
{
    struct termios  t;

    if (tcgetattr(STDIN_FILENO, &t) == -1)
        return ;
    t.c_lflag &= ~ECHOCTL;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void	enable_echoctl(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return ;
	term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
