/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <aboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:46:28 by aboutale          #+#    #+#             */
/*   Updated: 2024/10/31 21:21:52 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		temp = *lst;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}
/* #include <stdio.h>

int main()
{
	char *str1 = "ok";
	char *str2 = "daccor";
	char *str3 = "biensur";
	
	t_list *node1= ft_lstnew(str1);
	t_list *node2 = ft_lstnew(str2);
	t_list *node3 = ft_lstnew(str3);
	
	node1->next = node3;
	
	printf(" adresse du premier maillon : %p\n",(char *)node1->content);
	printf("adresse du secondmaillon : %p\n", (char *)node2->content);
	printf("adresse du troisieme maillon : %p\n", (char *)node3->content);

	ft_lstadd_back(&node1, node2);
	

	printf(" adresse du premier maillon : %s\n",(char *)node1->content);
	printf("adresse du secondmaillon : %s\n", (char *)node2->content);
	printf("adresse du troisieme maillon : %s\n", (char *)node3->content); 
	 while (node1 != NULL)
	{
		printf("%p\n",(char *)node1->content);
		node1 = node1->next;
	}
} */
