/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <taaikiazerolier@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:39:28 by mlavry            #+#    #+#             */
/*   Updated: 2024/10/15 10:50:20 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

/*int main()
{
    char chars[] = {'A', '0', '1', '*', '9', 'm'};
    int i;

    for (i = 0; i < 6; i++) {
        if (ft_isdigit(chars[i])) {
            printf("Le caractère '%c' est un chiffre.\n", chars[i]);
        }
		else {
        printf("Le caractère '%c' n'est pas un chiffre.\n", chars[i]);
        }
    }

    return 0;
}*/
