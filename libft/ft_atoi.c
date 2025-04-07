/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <aboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:54:12 by aboutale          #+#    #+#             */
/*   Updated: 2025/01/23 18:13:59 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#include <stdio.h>

int	ft_atoi(const char *nptr)
{
	int	result;
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	result = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		result = result * 10 + (nptr[i] - '0');
		if (result <= INT_MIN || result >= INT_MAX)
			return (printf("Error\n"));
		i++;
	}
	return (result * sign);
}
/* 
#include <stdlib.h>
#include <stdio.h>

int main()

{
    char tab[]= " -2255444788545445545858585 ";
    printf("%d \n", ft_atoi(tab));
    printf("%d \n", atoi(tab));
    return (0);
}
 */
