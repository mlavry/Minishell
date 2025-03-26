/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <taaikiazerolier@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:47:37 by mlavry            #+#    #+#             */
/*   Updated: 2025/01/06 18:11:56 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>

char	*ft_strrchr(const char *s, int c)
{
	char	*temp;

	temp = 0;
	while (*s)
	{
		if (*s == (unsigned char)c)
			temp = (char *)s;
		s++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s);
	return (temp);
}

/* int main(void)
{
    char str[] = "Hello, world!";
    char *result;

    result = ft_strrchr(str, 'o');
    if (result)
        printf("Last occurrence of 'o' found at: %s\n", result);
    else
        printf("'o' not found\n");

    return 0;
} */
