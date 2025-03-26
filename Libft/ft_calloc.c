/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <taaikiazerolier@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:41:41 by mlavry            #+#    #+#             */
/*   Updated: 2024/11/21 14:38:56 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	void			*ptr;
	size_t			total_size;
	unsigned char	*final;

	total_size = n * size;
	if (n != 0 && total_size / n != size)
		return (0);
	ptr = malloc(total_size);
	if (ptr == 0)
		return (0);
	final = (unsigned char *)ptr;
	while (total_size)
	{
		*final = 0;
		total_size--;
		final++;
	}
	return (ptr);
}

/*int main(void)
{
    int *arr;
    size_t n = 5;
    size_t size = sizeof(int);

    arr = (int *)ft_calloc(n, size);

    if (arr == NULL)
    {
        printf("Allocation échouée\n");
        return (1);
    }

    printf("Contenu du tableau alloué et initialisé à zéro :\n");
    for (size_t i = 0; i < n; i++)
    {
        printf("arr[%zu] = %d\n", i, arr[i]);
    }

    free(arr);

    return 0;
}*/
