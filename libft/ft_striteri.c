/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <aboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:07:27 by aboutale          #+#    #+#             */
/*   Updated: 2024/10/24 19:23:16 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	i;

	i = 0;
	if (!s || !f)
		return ;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
/*   void ftoupper (unsigned int i , char *str)
{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] = str[i] - 32;
}
#include <stdio.h>

int main()

{

	char tab[] = "bonjourcommentcava";
	printf("%s\n",tab);
	ft_striteri(tab, ftoupper);
	printf("%s",tab);
}
  */