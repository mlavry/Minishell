/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <aboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:09:12 by aboutale          #+#    #+#             */
/*   Updated: 2024/11/06 21:34:43 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	k;

	if ((!dst && size == 0))
		return (ft_strlen(src));
	i = ft_strlen(dst);
	j = ft_strlen(src);
	if (size == 0)
		return (j);
	if (size < i)
		return (j + size);
	k = 0;
	while (src[k] && (i + k < size - 1))
	{
		dst[i + k] = src[k];
		k++;
	}
	dst[i + k] = '\0';
	return (i + j);
}
/*  
 #include <stdio.h>
#include <bsd/string.h>
#include <string.h>
int main()

{
	//char dest[] = "bonjou";
	//char dest2[] ="bonjour";
	//char src2 [] = "bonjou";
    //char src[] = "bonjour"; 
    //printf("%zu\n", strlcat("bonjou","bonjour",14));
	printf("%zu\n",strlcat(dest,src,14));
	//printf("%s\n",dest); 
	//printf("%zu\n", ft_strlcat("bonjou","bonjour",14));
	//printf("%zu\n",ft_strlcat(NULL, NULL, 0));
	//printf("%s\n",dest2); 
	
    return 0;
}  */