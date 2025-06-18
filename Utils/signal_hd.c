/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_hd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 00:50:33 by mlavry            #+#    #+#             */
/*   Updated: 2025/06/18 15:50:19 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void  set_hd_signals(struct sigaction *old_int, struct sigaction *old_quit)
{
    struct sigaction  sa;
    sa.sa_handler = sigint_hd;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags   = 0;
    sigaction(SIGINT, &sa, old_int);
    sa.sa_handler = SIG_IGN;
    sigaction(SIGQUIT, &sa, old_quit);
}

void  restore_hd_signals(struct sigaction *old_int, struct sigaction *old_quit)
{
    sigaction(SIGINT,  old_int,  NULL);
    sigaction(SIGQUIT, old_quit, NULL);
}
