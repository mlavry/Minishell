/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <aboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:47:36 by aboutale          #+#    #+#             */
/*   Updated: 2024/10/21 11:52:37 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*str;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (str[i] == (unsigned char)c)
			return ((void *) &str[i]);
		i++;
	}
	return (NULL);
}

/* #include <stdio.h>

int main ()

{
	char tab[] = "hello";
	

	printf("%p",memchr(tab, '\0', 12));
	printf("%p",ft_memchr(tab, '\0', 12));
	return 0;

}
 */
