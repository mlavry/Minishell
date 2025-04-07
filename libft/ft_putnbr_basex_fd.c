/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_basex_fd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <aboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:56:20 by aboutale          #+#    #+#             */
/*   Updated: 2024/12/27 20:26:56 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_basex_fd(unsigned int n, int fd)
{
	char	*base;
	int		count;

	base = "0123456789ABCDEF";
	count = 0;
	if (n > 15)
	{
		count += ft_putnbr_basex_fd (n / 16, fd);
		ft_putnbr_basex_fd (n % 16, fd);
	}
	else
		ft_putchar_fd(base[n], fd);
	return (count + 1);
}
/* 
int main()
{
	printf("%X",ft_putnbr_basex_fd(-23,1));


} */
