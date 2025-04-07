/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:51:49 by aboutale          #+#    #+#             */
/*   Updated: 2024/10/17 08:57:07 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
/*
#include <stdio.h>
#include <ctype.h>
int main()
 
{
    ft_isdigit('5');
	isdigit('5');
    printf("%d", ft_isdigit('5'));
	printf("%d",isdigit('5'));
    return 0;
}
*/
