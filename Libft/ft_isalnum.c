/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <taaikiazerolier@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:50:14 by mlavry            #+#    #+#             */
/*   Updated: 2024/10/15 11:08:12 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>

int	ft_isalnum(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'));
}

/*int main()
{
    char chars[] = {'A', 'b', '1', '*', 'Z', ' '};
    int i;

    for (i = 0; i < 6; i++) {
        if (ft_isalnum(chars[i])) {
            printf("Le caractère '%c' est alphanumerique.\n", chars[i]);
        }
		else {
        printf("Le caractère '%c' n'est pas alphanumerique.\n", chars[i]);
        }
    }

    return 0;
}*/
