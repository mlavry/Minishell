/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:46:15 by mlavry            #+#    #+#             */
/*   Updated: 2025/06/02 18:45:39 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include <limits.h>

static int	ft_parse_digits(const char *nptr, int i, int sign)
{
	long	result;
	int		digit;

	result = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		digit = nptr[i] - '0';
		if (result > (LONG_MAX - digit) / 10)
			return (0);
		result = result * 10 + digit;
		i++;
	}
	result *= sign;
	if (result > INT_MAX || result < INT_MIN)
		return (0);
	return ((int)result);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;

	if (!nptr)
		return (0);
	i = 0;
	sign = 1;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	return (ft_parse_digits(nptr, i, sign));
}

/* int	main(void)
{
	char str1[] = " -1234ab567";
	char str2[] = "  569999999999999+7b8";
	char *str3 = NULL;

	int num1 = ft_atoi(str1);
	int num2 = ft_atoi(str2);
	int num3 = ft_atoi(str3);
	int num4 = ft_atoi("2147483648");
	int num5 = ft_atoi("2147483648");

	printf("num1 = %d\n", num1);
	printf("num2 = %d\n", num2);
	printf("num3 = %d\n", num3);
	printf("num4 = %d\n", num4);
	printf("num5 = %d\n", num5);

	return (0);
} */
