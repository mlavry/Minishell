/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <aboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:57:59 by aboutale          #+#    #+#             */
/*   Updated: 2024/10/29 12:15:45 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	j = 0;
	if (!s1)
		return (NULL);
	while (s1[j] && ft_strchr(set, s1[j]))
		s1++;
	i = ft_strlen(s1) - 1;
	while (s1[i] && ft_strrchr(set, s1[i]))
		i--;
	return (ft_substr(s1, j, i - j + 1));
}
/*  #include <stdio.h>

int main(int argc, char **argv)

{
	(void)argc;
	printf("%s\n", ft_strtrim(argv[1], argv[2]));
	//search("abcbonjourbca", 'bca');
	//printf("%d",search("abcde",'p'));
	free(argv[1]);	
} */
