/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <aboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:26:58 by aboutale          #+#    #+#             */
/*   Updated: 2024/10/17 21:26:20 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(src);
	if (size == 0)
		return (j);
	while (src[i] && (i < size - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (j);
}
/*
#include <stdio.h>
int main()

{
	char dest[] = "saluttttt";
	char src[] = "bonjour";
	printf("%zu", ft_strlcpy(dest, src, 5));
	printf("%s",dest);
	return 0;
}
*/
