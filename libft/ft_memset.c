/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <aboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:52:00 by aboutale          #+#    #+#             */
/*   Updated: 2024/10/21 18:01:47 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = c;
		i++;
	}
	return (s);
}
/*
#include <stdio.h>

int main (void)
{
	char tab[10]="hello";

//	ft_memset(tab, 'c',1);
//	memset(tab, 'c',1);
	printf("%s\n", (unsigned char *)ft_memset(tab,'c',1));
	printf("%s",(unsigned char *)memset(tab, 'c', 1));
	return 0;
}
 */
