/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <taaikiazerolier@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:25:50 by mlavry            #+#    #+#             */
/*   Updated: 2024/10/15 10:46:23 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>

int	ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

/*int main()
{
    char chars[] = {'A', 'b', '1', '*', 'Z', 'm'};
    int i;

    for (i = 0; i < 6; i++) {
        if (ft_isalpha(chars[i])) {
            printf("Le caractère '%c' est une lettre alphabétique.\n", chars[i]);
        }
		else {
        printf("Le caractère '%c' n'est pas alphabétique.\n", chars[i]);
        }
    }

    return 0;
}*/
