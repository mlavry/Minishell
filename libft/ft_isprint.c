/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <aboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:50:18 by aboutale          #+#    #+#             */
/*   Updated: 2024/10/21 11:49:47 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
/*
#include <stdio.h>
#include <ctype.h>

int main ()

{
	printf("%d",isprint(127));
	printf("%d",ft_isprint(127));
//	printf("%d",isprint('\n'));
//	printf("%d",ft_isprint('\n'));
	return 0;

}
*/
