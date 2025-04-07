/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <aboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:09:39 by aboutale          #+#    #+#             */
/*   Updated: 2024/11/05 20:30:38 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)

{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

// #include <stdio.h>
// #include <ctype.h>
// #include <string.h>

// int main()

// {
// 	char *str = NULL;
// 	// printf("%lu",strlen(str));
// 	printf("%lu",ft_strlen(str));
// 	return (0);
// }