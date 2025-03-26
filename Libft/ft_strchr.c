/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <taaikiazerolier@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:19:53 by mlavry            #+#    #+#             */
/*   Updated: 2025/01/06 18:34:30 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s);
	return (0);
}

/* int main(void)
{
    char str[] = "Hello, world!";
    char *result;

    result = ft_strchr(str, 'o');
    if (result)
        printf("First occurrence of 'o' found at: %s\n", result);
    else
        printf("'o' not found\n");

    return 0;
} */
