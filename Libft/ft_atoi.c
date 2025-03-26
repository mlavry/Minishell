/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <taaikiazerolier@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:46:15 by mlavry            #+#    #+#             */
/*   Updated: 2024/10/18 10:53:08 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>

int	ft_atoi(const char *nptr)
{
	int	i;
	int	result;
	int	sign;

	i = 0;
	result = 0;
	sign = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign++;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	if (sign % 2 != 0)
		result = -result;
	return (result);
}

/*int	main(void)
{
	char str1[] = " -1234ab567";
	char str2[] = "  56+7b8";

	int num1 = ft_atoi(str1);
	int num2 = ft_atoi(str2);

	printf("num1 = %d\n", num1);
	printf("num2 = %d\n", num2);

	return (0);
}*/
