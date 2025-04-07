/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsignedputnbr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <aboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:39:24 by aboutale          #+#    #+#             */
/*   Updated: 2024/12/27 20:11:29 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	unsignedputnbr(unsigned int n, int fd)
{
	if (n > 9)
	{
		ft_putnbr_fd (n / 10, fd);
		ft_putnbr_fd (n % 10, fd);
	}
	else
		ft_putchar_fd(n + '0', fd);
	return (countnumbers(n));
}
