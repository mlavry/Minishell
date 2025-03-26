/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <taaikiazerolier@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:13:20 by mlavry            #+#    #+#             */
/*   Updated: 2024/10/17 11:17:45 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	return (c);
}

/*int main(void)
{
    char test_chars[] = {'a', 'z', 'A', 'Z', '1', '!', 'm'};
    unsigned int i;

    printf("Testing ft_tolower function:\n\n");

    for (i = 0; i < sizeof(test_chars); i++)
    {
        char original = test_chars[i];
        char lower = ft_tolower(original);
        printf("Original: %c | Lower: %c\n", original, lower);
    }

    return (0);
}*/
