/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <taaikiazerolier@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 20:29:56 by mlavry            #+#    #+#             */
/*   Updated: 2025/04/07 20:30:49 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	o;

	i = 0;
	o = 0;
	while (dest[i] != '\0')
	{
		i++;
	}
	while (src[o] != '\0')
	{
		dest[i] = src[o];
		i++;
		o++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_strcmp(char *s1, char *s2)

{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

size_t  ft_strlen(const char *s) 
{
	size_t  i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char				*result;
	unsigned const char	*src;
	size_t				i;

	if (!s)
		return (NULL);
	src = (unsigned const char *) s;
	if (start >= ft_strlen(s))
		len = 0;
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	result = malloc((len + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = src[i + start];
		i++;
	}
	result[len] = '\0';
	return (result);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joi;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s2 || !s1)
		return (NULL);
	joi = (char *)ft_calloc(sizeof(*joi), (ft_strlen(s1) + ft_strlen(s2) + 1));
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
}

/* int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i ;

	i = 0;
	while ((i < n) && s1[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (i < n)
		return (s1[i] - s2[i]);
	return (0);
} */


/* void	free_paths(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->paths[i])
	{
		free(pipex->paths[i]);
		i++;
	}
	free(pipex->paths);
}

void	free_pipex(t_pipex *pipex)
{
	int	i;

	i = 0;
	if (!pipex)
		return ;
	while (pipex->cmds[i])
	{
		free(pipex->cmds[i]);
		i++;
	}
	free(pipex->cmds);
	if (pipex->infile >= 0)
		close(pipex->infile);
	if (pipex->outfile >= 0)
		close(pipex->outfile);
} */

void	free_split(char **split_paths)
{
	int	i;

	i = 0;
	if (!split_paths)
		return ;
	while (split_paths[i])
	{
		free(split_paths[i]);
		i++;
	}
	free(split_paths);
}

char	*findpath(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

/* void	get_path(t_pipex *pipex, char **args)
{
	int		i;
	char	*fullcmd;
	char	*tmp;

	i = 0;
	if (!args || !args[0])
		return ;
	if (access(args[0], X_OK) == 0)
		return ;
	while (pipex->paths[i])
	{
		tmp = ft_strjoin(pipex->paths[i], "/");
		fullcmd = ft_strjoin(tmp, args[0]);
		free(tmp);
		if (access(fullcmd, X_OK) == 0)
		{
			free(args[0]);
			args[0] = fullcmd;
			return ;
		}
		free(fullcmd);
		i++;
	}
} */
