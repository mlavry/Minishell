/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <aboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 18:20:18 by aboutale          #+#    #+#             */
/*   Updated: 2024/11/05 20:31:10 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <bsd/string.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	littlelen;

	if ((len <= 0 && !little) || (!big && len <= 0))
		return (NULL);
	i = 0;
	littlelen = ft_strlen(little);
	if (littlelen == 0)
		return ((char *) &big[i]);
	while (big[i] != '\0' && i < len)
	{
		if (big[i] == little[0])
		{
			j = 0;
			while (j < littlelen && (i + j) < len && big[i + j] == little[j])
				j++;
		}
		if (j == littlelen)
			return ((char *) &big[i]);
		i++;
	}
	return (NULL);
}
/* #include <stdio.h>
#include <string.h>

int main()

{
	char tab[] ="Gros porc Paul";
	char tab2[]= "porc";
	printf("%s\n", ft_strnstr(tab, tab2,9));
	printf("%s", strnstr(tab, tab2,9));
	return 0;
} 
 */