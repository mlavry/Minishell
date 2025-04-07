/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   countnumbers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <aboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:49:07 by aboutale          #+#    #+#             */
/*   Updated: 2024/12/27 20:26:37 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long int	countnumbers(long nb)
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
