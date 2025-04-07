/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <aboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:10:12 by aboutale          #+#    #+#             */
/*   Updated: 2025/01/23 18:30:04 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	size_t	i;
	size_t	count;

	if (!str)
		return (-1);
	va_start(ap, str);
	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%' && str[i + 1] != '\0')
		{
			count += printformat(str[i + 1], ap);
			i++;
		}
		else
		{
			ft_putchar_fd(str[i], 1);
			count++;
		}
		i++;
	}
	va_end(ap);
	return (count);
}

/*  #include <stdio.h>
#include <stddef.h>


int main()

{
 int i;
int j;
//int *p;
//int x = 42;

//p = &x;

i = 0;
j= 0; 
//void *ptr = 50;
//i = printf("%   %", ptr);
//j = ft_printf("%p\n", ptr);
//i =printf("%s %d %i\n", "HELLO", 14, 15);
//j =ft_printf("%s %d %i\n", "HELLO", 14, 15);
i = printf( "86 % d kelkchose\n");
j = ft_printf("86 %d kelkchose\n");
printf("%d\n", i);
ft_printf("%d", j);
 //i = printf("%d\n", 10);
//printf("%d\n", i);
//j = ft_printf("%d\n", 1);
//printf("%d\n",i);
//ft_printf("%d\n", j); 
//printf("%s\n", "Hellotththtth");
//ft_printf("%s", "HEllohh5hhththt");

//printf("NULL %s NULL\n", str);
//ft_printf("NULL %s NULL", str);
//i = printf("%c\n", 'c');
//printf("%i\n", i);
//i = printf("%p\n", p);
//printf("%d\n",i);
//j = ft_printf("%p\n", p);
//ft_printf("%d\n",j);
}  
  */