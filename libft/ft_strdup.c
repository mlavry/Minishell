/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <aboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:13:07 by aboutale          #+#    #+#             */
/*   Updated: 2024/10/21 11:53:56 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*str2;

	i = 0;
	str2 = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (str2 == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		str2[i] = s[i];
		i++;
	}
	str2[i] = '\0';
	return (str2);
}

/*
int main()

{
    char src[8] ="bonjour";
    char *str2; 

    str2 = ft_strdup(src);

    printf("%s\n%s",src, str2);
    free(str2);
    return(0);

}
*/
