/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fdd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <aboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:52:09 by aboutale          #+#    #+#             */
/*   Updated: 2024/12/27 20:25:46 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fdd(int n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fdd('-', fd);
		if (n == -2147483648)
		{
			write(fd, "2147483648", 10);
			return (11);
		}
		n = -n;
	}
	if (n > 9)
	{
		ft_putnbr_fdd (n / 10, fd);
		ft_putnbr_fdd (n % 10, fd);
	}
	else
		ft_putchar_fdd(n + '0', fd);
	return (countnumbers(n));
}
