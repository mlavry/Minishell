/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <taaikiazerolier@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:25:30 by mlavry            #+#    #+#             */
/*   Updated: 2024/11/04 15:45:07 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	while (n--)
		*d++ = *s++;
	return (dest);
}

/*int main (void)
{
	char src[] = "Bonjour5646546468";
	char dest[50];

	ft_memcpy(dest, src, sizeof (src) - 1);
	dest[sizeof (src) - 1] = '\0';
	printf("Tableau de dest : %s\n", dest);
	return (0);
}*/
