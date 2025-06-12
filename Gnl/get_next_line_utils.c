/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <aboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:25:33 by aboutale          #+#    #+#             */
/*   Updated: 2024/12/06 16:16:12 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s)
		while (s[i] != '\0')
			i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
		i++;
	dup = (char *)malloc(i + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;
	size_t	i;

	if (size != 0 && (nmemb * size) / size != nmemb)
		return (NULL);
	p = malloc(nmemb * size);
	if (!(p))
		return (NULL);
	i = 0;
	while (i < size * nmemb)
	{
		((char *)p)[i] = '\0';
		i++;
	}
	return (p);
}

/* char	*ft_strjoin(char *s1, char *s2)
{
	char	*joi;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s2 || !s1)
		return (NULL);
	joi = (char *)ft_calloc(sizeof(char), (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (joi == NULL)
		return (NULL);
	while (s1[i])
	{
		joi[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		joi[i + j] = s2[j];
		j++;
	}
	return (joi);
} */

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char) c)
			return ((char *)&s[i]);
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
