/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:24:22 by mlavry            #+#    #+#             */
/*   Updated: 2025/06/02 16:56:09 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dest;
	int		i;
	int		len;

	len = 0;
	if (!s)
		return (NULL);
	while (s[len])
		len++;
	dest = (char *)malloc((len + 1) * sizeof(char));
	if (!dest)
		return (0);
	i = 0;
	while (i < len)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/*int main(void)
{
    char *original = "Bonjour";
    char *copie = ft_strdup(original);

    if (copie != NULL) {
        printf("Copie : %s\n", copie);
        free(copie);
    } else {
        printf("Échec de la duplication de la chaîne.\n");
    }

    return 0;
}*/
