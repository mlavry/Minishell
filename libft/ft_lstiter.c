/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <aboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:16:23 by aboutale          #+#    #+#             */
/*   Updated: 2024/11/06 20:37:44 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst != NULL)
	{
		f(lst->content);
		lst = lst ->next;
	}
}
/* void	ft_tolowerslst(void *c)
{
	int i = 0;
	char *str = (char *)c;
	while(((char *) c)[i] != '\0')
			str[i]
	{
	if (((char *) c)[i] >= 'A' && ((char *) c)[i] <= 'Z')
		((char *) c)[i] += 32;
	i++;
	}
} */
/* #include <stdio.h>
#include <ctype.h>


int main()
{



	 char str[] = "BONJOUR";
	
	t_list *node = ft_lstnew(str);

	ft_lstiter(node, ft_tolowerslst);
		printf("%s",(char *)node->content);

	while (node != NULL)
	{
		printf("%s",(char *)node->content );
		node = node-> next;
	}
} */
