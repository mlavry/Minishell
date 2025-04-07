/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <aboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 18:02:09 by aboutale          #+#    #+#             */
/*   Updated: 2024/11/01 17:53:18 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((i < n) && s1[i])
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i < n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}
/*
#include <string.h>
#include <stdio.h>

int main()

{
    unsigned int n = 4;

    char tabs1[] = "Hello";
    char tabs2[] = "Hel";

    printf("%s\n%s\n%d\n", tabs1, tabs2, ft_strncmp(tabs1, tabs2, n));
    printf("%s\n%s\n%d\n", tabs1, tabs2, strncmp(tabs1, tabs2, n));
    return (0);
}
*/
