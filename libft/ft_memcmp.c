/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <aboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:12:02 by aboutale          #+#    #+#             */
/*   Updated: 2024/10/21 11:56:03 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	unsigned const char	*str1;
	unsigned const char	*str2;

	str1 = (unsigned const char *)s1;
	str2 = (unsigned const char *)s2;
	i = 0;
	while (i < n)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}
/* 
#include <string.h>
#include <stdio.h>

int main()

{


	char tab[] ="\xff\0\0\xaa\0\xde" ;
	char tab2[] ="\xff\0\0\xaa\0\xde";
	printf("%d\n",memcmp(tab,tab2,12));
	printf("%d\n",ft_memcmp(tab,tab2,12));
	printf("%s %s",tab,tab2);

	return 0;
}
 */
