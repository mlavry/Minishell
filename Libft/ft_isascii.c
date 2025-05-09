/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <taaikiazerolier@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:21:25 by mlavry            #+#    #+#             */
/*   Updated: 2024/10/15 11:50:51 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}

/*int main()
{
    char chars[] = {'126', 'b', '1', '*', '132', '-4'};
    int i;

    for (i = 0; i < 6; i++) {
        if (ft_isascii(chars[i])) {
            printf("Le caractère '%c' est un caractere ascii.\n", chars[i]);
        }
		else {
        printf("Le caractère '%c' n'est pas un caractere ascii.\n", chars[i]);
        }
    }

    return 0;
}*/
