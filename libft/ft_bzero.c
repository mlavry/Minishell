/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <aboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:58:40 by aboutale          #+#    #+#             */
/*   Updated: 2024/11/04 16:32:00 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*str;
	size_t	i;

	if (n == 0)
		return ;
	str = (char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}

/* #include<stdio.h>
int main() 
{
     char tab[10] = "Hello"; 
     printf("%s\n",tab);
     ft_bzero(tab, 3);
     printf("%s\n", tab);  
     return 0;
 }
 */

/*  #include <stdio.h>
#include <string.h>

int main(void)
{
	int i;

	i = 4;
 	char tab[] = "bonjour";
 	char tab2[] = "bonjour";
 //	printf("%s\n", tab); 
 //	printf("%s\n", tab2); 
 	ft_bzero(tab, i);
 	bzero(tab2,i);
 	printf("%s\n", tab + i ); 
 	printf("%s", tab2 + i );
 	return 0;
} */