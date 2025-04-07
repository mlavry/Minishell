/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <aboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 09:10:11 by aboutale          #+#    #+#             */
/*   Updated: 2024/11/06 20:34:14 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;
	size_t		i;

	if (!dest && !src && n == 0)
		return (NULL);
	d = (char *)dest;
	s = (const char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}
/* 
#include <stdio.h>
#include <string.h>

int main()

{
	size_t n;

	n=5;

	char src = "HELLO";
	char dest ="HELLO"; 
	ft_memcpy("HELLO","HELLO",n);
	ft_memcpy("HELLO","HELLO",1);
	printf("%s\n%s","HELLO", "HELLO", 1);
	return 0;

} */
