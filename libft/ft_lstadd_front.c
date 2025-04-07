/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <aboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:31:09 by aboutale          #+#    #+#             */
/*   Updated: 2024/10/31 20:25:35 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new ->next = *lst;
	*lst = new;
}
/* #include <stdio.h>

int main()
{

	char *str = "Hello";
	char *str2 = "Hello2";
	char *strnew = "Hello 3";

	t_list *node = ft_lstnew(str);
	t_list *node2 = ft_lstnew(str2);
	t_list *node3 = ft_lstnew(strnew);

	node->next = node2;
	

	printf(" contenu du premier maillon : %s\n",(char *)node->content);
	printf("contenu du secondmaillon : %s\n", (char *)node2->content);
	printf("contenu du troisieme maillon : %s\n", (char *)node3->content);


	 ft_lstadd_front(&node , node3);

	while (node != NULL)
	{
		printf("%s\n",(char *)node->content);
		node = node->next;
	} 

	 printf(" 1er apres fonction :%s\n", (char *)node->content);
	 printf("2nd apres fonction :%s\n", (char *)node->next->content);
	 printf("3eme apres fonction :%s", (char *)node->next->next->content);
 
	return 0;
} 
*/