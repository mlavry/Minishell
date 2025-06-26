/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:07:25 by mlavry            #+#    #+#             */
/*   Updated: 2025/06/26 20:23:28 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	hd_abort(char *line)
{
	free(line);
	return (-1);
}

static int	hd_is_end(char *line, char *delim)
{
	char	*nl;

	nl = ft_strchr(line, '\n');
	if (nl)
		*nl = '\0';
	if (ft_strcmp(line, delim) == 0)
		return (1);
	return (0);
}

static void	hd_write(int fd, char *line)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

static int	heredoc_loop(t_data *d, int idx, char *delim, int fd)
{
	char	*line;

	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO, 0);
		if (!line)
			return (1);
		if (g_exit_status == 130)
			return (hd_abort(line));
		if (hd_is_end(line, delim))
		{
			free(line);
			break ;
		}
		if (d->expand_hd[idx])
			replace_dollars_heredocs(d, &line);
		hd_write(fd, line);
		free(line);
	}
	return (0);
}

int	write_heredoc(t_data *d, int idx, char *delim, int fd)
{
	struct sigaction	old_int;
	int					saved;
	int					ret;

	saved = g_exit_status;
	disable_echoctl();
	hd_set_signals(&old_int);
	g_exit_status = 0;
	ret = heredoc_loop(d, idx, delim, fd);
	enable_echoctl();
	hd_restore_signals(&old_int);
	if (ret == 1 && g_exit_status != 130)
	{
		printf("\nminishell: warning: here-document delimited by end-of-file ");
		printf("(wanted `%s')\n", delim);
	}
	if (g_exit_status != 130)
		g_exit_status = saved;
	if (ret == -1 || g_exit_status == 130)
		return (-1);
	return (0);
}
