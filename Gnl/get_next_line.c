/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <aboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:33:23 by aboutale          #+#    #+#             */
/*   Updated: 2025/03/13 17:48:56 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	readbuffer(int fd, char **buffer)
{
	int		readchar;
	char	*temp ;
	char	*newbuffer;

	temp = malloc(sizeof(char) * BUFFER_SIZE +1);
	if (!temp)
		return (-1);
	readchar = read(fd, temp, BUFFER_SIZE);
	if (readchar < 0)
	{
		free(temp);
		return (readchar);
	}
	temp[readchar] = '\0';
	newbuffer = ft_strjoin(*buffer, temp);
	free(temp);
	if (!newbuffer)
		return (-1);
	free(*buffer);
	*buffer = newbuffer;
	return (readchar);
}

char	*extractline(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	line = NULL;
	i = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] != '\n' && buffer[i])
		i++;
	if (buffer[i] == '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = buffer[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

int	refreshbuffer(char **buffer)
{
	int		i;
	char	*newbuffer;

	i = 0;
	while ((*buffer)[i] != '\n' && (*buffer)[i] != '\0')
		i++;
	newbuffer = NULL;
	if ((*buffer)[i] == '\n')
	{
		if (ft_strlen(*buffer) - i > 0)
		{
			newbuffer = ft_strdup(&(*buffer)[i + 1]);
			if (!newbuffer)
				return (-1);
		}
		free(*buffer);
		*buffer = newbuffer;
	}
	else
	{
		free(*buffer);
		*buffer = NULL;
	}
	return (0);
}

int	nextline(int fd, char **buffer, char **line)
{
	int	readchar;

	readchar = readbuffer(fd, buffer);
	while ((readchar > 0))
	{
		if (ft_strchr(*buffer, '\n'))
		{
			*line = extractline(*buffer);
			if (!*line)
				return (-1);
			if (refreshbuffer(buffer) == -1)
				return (-1);
			return (1);
		}
		readchar = readbuffer(fd, buffer);
	}
	if (readchar == 0 && *buffer && **buffer != '\0')
	{
		*line = ft_strdup(*buffer);
		free(*buffer);
		*buffer = NULL;
		return (1);
	}
	free(*line);
	return (0);
}

char	*get_next_line(int fd, int code)
{
	static char	*buffer[1024];
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1023)
		return (NULL);
	if (code == 1)
		return (free(buffer[fd]), buffer[fd] = NULL, NULL );
	if (!buffer[fd])
		buffer[fd] = ft_strdup("");
	if (!buffer[fd])
		return (NULL);
	if (*buffer[fd] && ft_strchr(buffer[fd], '\n'))
	{
		line = extractline(buffer[fd]);
		refreshbuffer(&buffer[fd]);
		return (line);
	}
	if (nextline(fd, &buffer[fd], &line) > 0)
		return (line);
	free(buffer[fd]);
	buffer[fd] = NULL;
	return (NULL);
}
