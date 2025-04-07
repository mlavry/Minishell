/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <aboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:45:46 by aboutale          #+#    #+#             */
/*   Updated: 2024/11/01 18:01:55 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}
/*
#include <ctype.h>
#include <stdio.h>

int main()
{
	printf("%d", ft_toupper('A'));
	printf("%d", toupper('A'));
	return 0;
}*/
