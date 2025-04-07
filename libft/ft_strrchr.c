/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <aboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:54:56 by aboutale          #+#    #+#             */
/*   Updated: 2024/10/21 11:51:23 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}
/* #include <stdio.h>

int main ()

{
	char tab[] = "zhel1l\0oeiiii";
	printf("%s\n",strrchr(tab, 'z'));
	printf("%s\n",ft_strrchr(tab, 'z'));
	return 0;

}
 */
