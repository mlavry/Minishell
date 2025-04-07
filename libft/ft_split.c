/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <aboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:37:55 by aboutale          #+#    #+#             */
/*   Updated: 2024/11/04 16:39:29 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	countingwords(char const *s, char c)
{
	int	i;
	int	counting;

	i = 0;
	counting = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i +1] == '\0'))
			counting++;
		i++;
	}
	return (counting);
}

static int	wordlong(char const *s, char c)
{
	size_t	l;

	l = 0;
	while (*s && *s == c)
		s++;
	while (*s && *s != c)
	{
		l++;
		s++;
	}
	return (l);
}

static void	freemalloc(char **tab, size_t i)
{
	size_t	j;

	j = 0;
	if (tab[i] == NULL)
	{
		while (j < i)
		{
			free(tab[j]);
			j++;
		}
	}
	free(tab);
}

static char	**fill(char **tab, const char *s, char c)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			len = wordlong(s, c);
			tab[i] = ft_substr(s, 0, len);
			if (!tab[i])
			{
				freemalloc(tab, i);
				return (NULL);
			}
			i++;
			s += len;
		}
	}
	tab[i] = NULL;
	return (tab);
}

char	**ft_split(const char *s, char c)
{
	int		words;
	char	**tab;

	if (!s)
		return (NULL);
	words = countingwords(s, c);
	tab = malloc(sizeof(char *) * (words +1));
	if (!tab)
		return (NULL);
	return (fill(tab, s, c));
}

/* #include <stdio.h>
 
int main()
{
	
 const char *tab = "bonjour comment ça va aujourd'hui";
 char d = ' ';
    
    char **res = ft_split(tab, d);
    if (res == NULL) {
        printf("ERROR\n");
        return 1;
    }

    size_t i = 0;
    while (res[i] != NULL) 
	{
        printf("%s\n", res[i]);
         free(res[i]);  
        i++;
    }
    
    free(res); 

    return 0;
}   */
