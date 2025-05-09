/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <taaikiazerolier@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:49:15 by mlavry            #+#    #+#             */
/*   Updated: 2024/12/18 14:14:57 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_printpercent(void)
{
	write(1, "%", 1);
	return (1);
}

int	ft_format(va_list args, const char format)
{
	int	printlen;

	printlen = 0;
	if (format == 'c')
		printlen += ft_printchar(va_arg(args, int));
	else if (format == 's')
		printlen += ft_printstr(va_arg(args, char *));
	else if (format == 'p')
		printlen += ft_printptr(va_arg(args, unsigned long));
	else if (format == 'd')
		printlen += ft_printnbr(va_arg(args, int));
	else if (format == 'i')
		printlen += ft_printnbr(va_arg(args, int));
	else if (format == 'u')
		printlen += ft_uprintnbr(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		printlen += ft_print_hex(va_arg(args, unsigned int), format);
	else if (format == '%')
		printlen += ft_printpercent();
	return (printlen);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		printlen;

	i = 0;
	printlen = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			printlen += ft_format(args, str[i + 1]);
			i++;
		}
		else
			printlen += ft_printchar(str[i]);
		i++;
	}
	va_end(args);
	return (printlen);
}

/* #include <stdio.h>

int main()
{
	int ptr;

	ptr = 1;

	printf("%%\n");
	ft_printf("%%\n");


} */
