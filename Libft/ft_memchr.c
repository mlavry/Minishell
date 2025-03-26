/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <taaikiazerolier@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:35:36 by mlavry            #+#    #+#             */
/*   Updated: 2024/10/23 14:24:01 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*ptr;
	size_t				i;

	ptr = (const unsigned char *) s;
	i = 0;
	while (i < n)
	{
		if (ptr[i] == (unsigned char) c)
		{
			return ((void *)(ptr + i));
		}
		i++;
	}
	return (0);
}

/*int	main(void)
{
	char	buffer[20] = "Bonjour";
	char	*result;

	result = ft_memchr(buffer, '5', sizeof(buffer) - 1);
	if (result != NULL)
		printf("Carac trouvé à l'adresse : %p, rest : %s\n", result, result);
	else
		printf("Caractère non trouvé.\n");
	return (0);
}*/
