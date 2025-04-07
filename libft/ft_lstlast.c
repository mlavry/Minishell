/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <aboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:35:16 by aboutale          #+#    #+#             */
/*   Updated: 2025/01/23 18:14:58 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
/*  #include <stdio.h>

int main()

{
	char *str ="bonjour";
	char *str2 = "bjr";
	char *str3 = "bijour";

	t_list *node1 = ft_lstnew(str);
	t_list *node2 = ft_lstnew(str2);
	t_list *node3 = ft_lstnew(str3);
	
	printf("%p\n",(char *)node3);

	node1-> next = node2;
	node2->next = node3;

	ft_lstlast(node1);
	printf("%p", (char *)ft_lstlast(node1));


	
}  */