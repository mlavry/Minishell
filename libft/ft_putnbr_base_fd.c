/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <aboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:19:23 by aboutale          #+#    #+#             */
/*   Updated: 2024/12/27 20:11:29 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_base_fd(unsigned long n, int fd)
{
	char	*base;
	int		count;

	base = "0123456789abcdef";
	count = 0;
	if (n > 15)
	{
		count += ft_putnbr_base_fd (n / 16, fd);
		ft_putnbr_base_fd (n % 16, fd);
	}
	else
		ft_putchar_fd(base[n], fd);
	return (count + 1);
}
