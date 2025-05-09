/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <taaikiazerolier@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:41:09 by mlavry            #+#    #+#             */
/*   Updated: 2024/10/23 14:25:02 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *) s;
	while (n)
	{
		*ptr = (unsigned char) c;
		n--;
		ptr++;
	}
	return (s);
}

/*int	main(void)
{
	char	buffer[20];

	ft_memset(buffer, '0', sizeof (buffer) - 1);
	buffer[19] = '\0';
	printf("Tableau cree : %s\n", buffer);
	return (0);
}*/
