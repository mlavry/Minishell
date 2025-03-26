/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <taaikiazerolier@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:26:06 by mlavry            #+#    #+#             */
/*   Updated: 2024/11/21 15:50:45 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	char	*start;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = 0;
	while (s1[len1])
		len1++;
	len2 = 0;
	while (s2[len2])
		len2++;
	result = (char *)malloc(len1 + len2 + 1);
	if (!result)
		return (NULL);
	start = result;
	while (*s1)
		*result++ = *s1++;
	while (*s2)
		*result++ = *s2++;
	*result = '\0';
	return (start);
}

/*#include <stdio.h>

int main() {
    const char *str1 = "Hello, ";
    const char *str2 = "world!";
    char *result = ft_strjoin(str1, str2);

    if (result) {
        printf("%s\n", result); // Affiche "Hello, world!"
        free(result); // N'oublie pas de libérer la mémoire allouée
    }

    return 0;
}*/
