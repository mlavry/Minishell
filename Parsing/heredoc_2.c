/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 20:26:29 by mlavry            #+#    #+#             */
/*   Updated: 2025/06/27 00:35:28 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*heredoc_tmp(void)
{
	static int	i = 0;
	char		*num;
	char		*filename;

	num = ft_itoa(i++);
	filename = ft_strjoin("/tmp/heredoc_%d.tmp", num);
	if (!filename)
	{
		free(num);
		return (NULL);
	}
	free(num);
	return (filename);
}

static int	create_tmp_heredoc_file(char **filename)
{
	*filename = heredoc_tmp();
	if (!*filename)
		return (-1);
	return (open(*filename, O_WRONLY | O_CREAT | O_TRUNC | __O_CLOEXEC, 0600));
}

static int	open_heredoc_read(t_cmd *cur, char *filename)
{
	if (cur->fd_in != STDIN_FILENO)
		close(cur->fd_in);
	cur->fd_in = open(filename, O_RDONLY);
	if (cur->fd_in == -1)
	{
		perror("open heredoc read");
		unlink(filename);
		free(filename);
		return (0);
	}
	if (cur->heredoc_file)
	{
		unlink(cur->heredoc_file);
		free(cur->heredoc_file);
	}
	cur->heredoc_file = filename;
	return (1);
}

int	handle_heredoc(t_data *data, t_token **tokens, t_cmd *cur)
{
	char	*delimiter;
	char	*tmp_filename;
	int		tmp_fd;

	delimiter = (*tokens)->next->str;
	tmp_fd = create_tmp_heredoc_file(&tmp_filename);
	if (tmp_fd == -1)
		return (0);
	if (write_heredoc(data, data->hd_idx, delimiter, tmp_fd) == -1)
	{
		close(tmp_fd);
		unlink(tmp_filename);
		free(tmp_filename);
		g_exit_status = 130;
		return (0);
	}
	close(tmp_fd);
	data->hd_idx++;
	get_next_line(STDIN_FILENO, 1);
	return (open_heredoc_read(cur, tmp_filename));
}
