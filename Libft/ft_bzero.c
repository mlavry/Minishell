/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:42:21 by mlavry            #+#    #+#             */
/*   Updated: 2025/06/02 16:36:42 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	if (!s && n > 0)
		return ;
	ptr = (unsigned char *)s;
	while (n)
	{
		*ptr = 0;
		n--;
		ptr++;
	}
}

/*int main (void)
{
	char buffer[5] = "1234";
	int i = 0;
	ft_bzero(buffer, sizeof(buffer));
	while (i < 5)
	{
		printf("%d", buffer[i]);
		i++;
	}
	return (0);
}*/
