/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <taaikiazerolier@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:51:33 by mlavry            #+#    #+#             */
/*   Updated: 2024/10/15 12:02:04 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>

int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}

/*int main()
{
	char chars[] = {'A', '0', '1', '*', '\n', 'm'};
    int i;

    for (i = 0; i < 6; i++) {
        if (ft_isprint(chars[i])) {
            printf("Le caractère '%c' est imprimable.\n", chars[i]);
        }
		else {
        printf("Le caractère '%c' n'est pas imprimable.\n", chars[i]);
        }
    }

    return 0;
}*/
