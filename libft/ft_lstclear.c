/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <aboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:54:51 by aboutale          #+#    #+#             */
/*   Updated: 2024/11/04 17:07:26 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;

	if (lst == NULL || del == NULL)
		return ;
	while (*lst != NULL)
	{
		temp = *lst;
		*lst = (*lst)->next;
		ft_lstdelone(temp, del);
	}
}

/* #include <stdio.h>

void del(void *content)
{
    // Si content a été alloué dynamiquement, libérez-le
    free(content);
} */
/* int main()

{	
	char *str1 = ft_strdup("pkpk");
	char *str2 =ft_strdup("paskpask");
	char *str3 = ft_strdup("okok");

	t_list *node1 = ft_lstnew(str1);
	t_list *node2 = ft_lstnew(str2);
	t_list *node3= ft_lstnew(str3);

	printf("%s\n",(char *)node1->content);
	printf("%s\n",(char *)node2->content);
	printf("%s\n",(char *)node3->content);
	
	
	
	node1->next =node2;
	node2->next = node3;
 
	ft_lstclear(&node1, del);
 
	printf("%s\n",(char *)node1->content);
	printf("%s\n",(char *)node2->content);
	printf("%s\n",(char *)node3->content);
	
 
	  if (node1 != NULL)
	{
		printf("%s",(char *)node1->content);
		node1 = node1->next;

	}
	else
	printf("THE LIST IS CLEAN");
} */