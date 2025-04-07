/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <aboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:38:51 by aboutale          #+#    #+#             */
/*   Updated: 2024/11/01 17:00:28 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
/*
#include <stdio.h>

 int main()


{
	char tab [] = " bonjour";
	char tab2 [] = " ca va";
	
	ft_strjoin(tab,tab2);
	printf("%s", ft_strjoin(tab, tab2));
	free(tab2);
	return 0;

	
} */