/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:46:15 by mlavry            #+#    #+#             */
/*   Updated: 2025/06/03 00:49:00 by mlavry           ###   ########.fr       */
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

/* int	main(void)
{
	char str1[] = " -1234ab567";
	char str2[] = "  569999999999999+7b8";
	char *str3 = "0";

	int num1 = ft_atoi(str1);
	int num2 = ft_atoi(str2);
	int num3 = ft_atoi(str3);
	int num4 = ft_atoi("00001");
	int num5 = ft_atoi("214748364");

	printf("num1 = %d\n", num1);
	printf("num2 = %d\n", num2);
	printf("num3 = %d\n", num3);
	printf("num4 = %d\n", num4);
	printf("num5 = %d\n", num5);

	return (0);
} */
