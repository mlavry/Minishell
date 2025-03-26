/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <taaikiazerolier@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:08:26 by mlavry            #+#    #+#             */
/*   Updated: 2024/12/18 14:15:51 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar(char c)
{
	write (1, &c, 1);
}

int	ft_ptr_len(unsigned long num)
{
	int	len;

	len = 0;
	if (num == 0)
		return (1);
	while (num != 0)
	{
		len++;
		num = num / 16;
	}
	return (len);
}

void	ft_put_ptr(unsigned long num)
{
	if (num >= 16)
	{
		ft_put_ptr(num / 16);
		ft_put_ptr(num % 16);
	}
	else
	{
		if (num <= 9)
			ft_putchar(num + '0');
		else
			ft_putchar(num - 10 + 'a');
	}
}

int	ft_printptr(unsigned long ptr)
{
	int	printlen;

	printlen = 0;
	if (ptr == 0)
		printlen += write(1, "(nil)", 5);
	else
	{
		printlen += write(1, "0x", 2);
		ft_put_ptr(ptr);
		printlen += ft_ptr_len(ptr);
	}
	return (printlen);
}
