/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <aboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:12:14 by aboutale          #+#    #+#             */
/*   Updated: 2024/10/24 21:46:12 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*str;

	if (!s)
		return (NULL);
	str = (char *)malloc(sizeof(char) * ft_strlen(s) +1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
/* char transfo(unsigned int i, char c)
	{
		(void) i;
		
		c = c + 1;
		return (c);
	}

	#include <stdio.h>
	
	int main()

	{
		char tab[] = "anmintq";
		printf("%s", ft_strmapi(tab, transfo));
		free(tab);
		return 0;
	} */