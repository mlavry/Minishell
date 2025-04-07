/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:33:04 by aboutale          #+#    #+#             */
/*   Updated: 2024/10/17 15:12:06 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

/*
#include <stdio.h>
#include <ctype.h>
int main()

{
	ft_isalpha(-2147483648);
	printf("%d", ft_isalpha(-2147483648));
	printf("%d",isalpha(-2147483648));
	return 0;
}
*/		
