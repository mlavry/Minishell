/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util_convert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <taaikiazerolier@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:25:28 by mlavry            #+#    #+#             */
/*   Updated: 2024/12/18 14:25:48 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* static int	numlen(int n)
{
	int	len;

	len = 1;
	if (n < 0)
		len++;
	while (n / 10 != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
} */

int	u_numlen(unsigned int n)
{
	int	len;

	len = 0;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

/* char	*ft_itoa(int n)
{
	unsigned int	num;
	int				len;
	char			*str;

	len = numlen(n);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	str [len--] = '\0';
	if (n < 0)
	{
		str [0] = '-';
		num = -n;
	}
	else
		num = n;
	while (num >= 10)
	{
		str [len--] = (num % 10) + '0';
		num /= 10;
	}
	str [len] = num + '0';
	return (str);
} */

char	*ft_uitoa(unsigned int n)
{
	int				len;
	char			*str;

	len = u_numlen(n);
	str = (char *)malloc(len + 1);
	if (!str)
		return (0);
	str [len--] = '\0';
	while (n != 0)
	{
		str [len] = n % 10 + 48;
		n = n / 10;
		len--;
	}
	return (str);
}
