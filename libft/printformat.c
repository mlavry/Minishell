/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printformat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <aboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:39:07 by aboutale          #+#    #+#             */
/*   Updated: 2025/01/23 18:30:53 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	spes(va_list ap)
{
	char	*str;
	size_t	i;

	i = 0;
	str = va_arg(ap, char *);
	if (str == NULL)
	{
		ft_putstr_fd("(null)", 1);
		i = 6;
		return (i);
	}
	ft_putstr_fd(str, 1);
	while (str[i] != '\0')
		i++;
	return (i);
}

static int	spep(va_list ap)
{
	size_t			i;
	void			*ptr;
	unsigned long	add;

	i = 0;
	ptr = va_arg(ap, void *);
	add = (unsigned long)ptr;
	if (ptr == NULL)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	ft_putstr_fd("0x", 1);
	i += 2;
	i = ft_putnbr_base_fd((unsigned long)add, 1) + i;
	return (i);
}

static int	printint( va_list ap)
{
	size_t	k;
	size_t	i;

	i = 0;
	k = va_arg(ap, int);
	ft_putnbr_fd(k, 1);
	i = i + countnumbers(k);
	return (i);
}

static int	printunsignedint(va_list ap)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = va_arg(ap, unsigned int);
	unsignedputnbr(j, 1);
	i = i + unsignedcountnumbers(j);
	return (i);
}

int	printformat(char spe, va_list ap)
{
	int		i;

	i = 0;
	if (spe == 'c')
		i = ft_putchar_fdd(va_arg(ap, int), 1);
	else if (spe == 's')
		i = spes(ap);
	else if (spe == 'p')
		i = spep(ap);
	else if (spe == 'd' )
		i = printint(ap);
	else if (spe == 'i')
		i = printint(ap);
	else if (spe == 'u')
		i = printunsignedint(ap);
	else if (spe == 'x')
		i = ft_putnbr_base_fd((va_arg(ap, unsigned int)), 1);
	else if (spe == 'X')
		i = ft_putnbr_basex_fd((va_arg(ap, unsigned int)), 1);
	else if (spe == '%')
		i = ft_putchar_fdd('%', 1) + i;
	else
		i = ft_putchar_fdd('%', 1);
	return (i);
}
