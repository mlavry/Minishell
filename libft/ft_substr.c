/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <aboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:33:24 by aboutale          #+#    #+#             */
/*   Updated: 2024/11/04 19:03:04 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char				*result;
	unsigned const char	*src;
	size_t				i;

	if (!s)
		return (NULL);
	src = (unsigned const char *) s;
	if (start >= ft_strlen(s))
		len = 0;
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	result = malloc((len + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = src[i + start];
		i++;
	}
	result[len] = '\0';
	return (result);
}

/* #include <stdio.h>
#include <string.h>

int main (int argc, char ** argv)
{
	char * output_ft;
	char * str = argv[1];
	unsigned int start = atoi(argv[2]);
	size_t len = atoi(argv[3]);
	
   output_ft = ft_substr(str, start, len);
   printf("%s\n", output_ft);
	
   

   return 0;
} */