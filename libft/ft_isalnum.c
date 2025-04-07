/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:14:09 by aboutale          #+#    #+#             */
/*   Updated: 2024/10/17 09:14:24 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (ft_isdigit(c) || ft_isalpha(c))
		return (1);
	return (0);
}
/*
#include <stdio.h>
#include <ctype.h>

	int main()
{
	ft_isalnum('a');
	isalnum('z');
	printf("%d",ft_isalnum('z'));
	printf("%d",isalnum('z'));
	return 0;
}
*/
