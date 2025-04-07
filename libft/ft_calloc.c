/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <aboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 00:04:56 by aboutale          #+#    #+#             */
/*   Updated: 2024/11/05 20:31:01 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;
	size_t	i;

	if (size != 0 && (nmemb * size) / size != nmemb)
		return (NULL);
	p = malloc(nmemb * size);
	if (!(p))
		return (NULL);
	i = 0;
	while (i < size * nmemb)
	{
		((char *)p)[i] = '\0';
		i++;
	}
	return (p);
}
/* 
#include <stdio.h>

int main()

{
	char *tab = "HELLO";
	
	tab = ft_calloc(sizeof(char *),6);
	if (tab == 0 )
		printf("ca fonctionne");
	//free(tab);
	return 0;	
}
 */
