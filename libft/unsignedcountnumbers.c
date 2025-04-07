/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsignedcountnumbers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <aboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:39:11 by aboutale          #+#    #+#             */
/*   Updated: 2024/12/27 20:11:29 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	unsignedcountnumbers(unsigned int nb)
{
	size_t	count;

	count = 0;
	if (nb < 0)
	{
		nb *= -1;
		count = count + 1;
	}
	if (nb == 0)
		count = 1;
	while (nb)
	{
		nb = nb / 10;
		count++;
	}
	return (count);
}
