/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <taaikiazerolier@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:16:45 by mlavry            #+#    #+#             */
/*   Updated: 2024/10/23 14:26:24 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

char	*ft_strnstr(const char *big,	const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*little == '\0')
		return ((char *)(big));
	while (big[i] != '\0' && i < len)
	{
		j = 0;
		while (big[j + i] == little[j] && (i + j) < len)
		{
			if (little [j + 1] == '\0')
				return ((char *)(&big[i]));
			j++;
		}
		i++;
	}
	return (0);
}

/*int	main(void)
{
	char str[] = "Bonjour tout le monde";
	char to_find[] = "toit";

	char *result = ft_strnstr(str, to_find, sizeof (str));
	if (result != 0)
		printf("Resultat :%s\n", result);
	else
		printf("Erreur.\n");
	return (0);
}*/
