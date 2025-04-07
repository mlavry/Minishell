/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <aboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:09:39 by aboutale          #+#    #+#             */
/*   Updated: 2024/11/06 20:12:02 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;

	i = 0;
	if (dest == 0 && src == 0)
		return (NULL);
	if (dest < src)
	{
		while (i < n)
		{
			((char *)dest)[i] = ((char *)src)[i];
			i++;
		}
	}
	else
	{
		i = n;
		while (i > 0)
		{
			i--;
			((char *)dest)[i] = ((char *)src)[i];
		}
	}
	return (dest);
}
/*  #include <stdio.h>

int main()

{
	char tab[0] ;
	char tab2[0];
	printf("%p\n",memmove(NULL, NULL,0));
	printf("%p\n",ft_memmove(NULL, NULL, 0));
	printf("%s\n", tab2);
	return 0;
}
 */
