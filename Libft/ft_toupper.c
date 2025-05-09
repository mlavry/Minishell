/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <taaikiazerolier@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:43:00 by mlavry            #+#    #+#             */
/*   Updated: 2024/10/17 11:05:18 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}

/*int main(void)
{
    char test_chars[] = {'a', 'z', 'A', 'Z', '1', '!', 'm'};
    unsigned int i;

    printf("Testing ft_toupper function:\n\n");

    for (i = 0; i < sizeof(test_chars); i++)
    {
        char original = test_chars[i];
        char upper = ft_toupper(original);
        printf("Original: %c | Upper: %c\n", original, upper);
    }

    return 0;
}*/
