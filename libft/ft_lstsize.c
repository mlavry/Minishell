/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <aboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:00:43 by aboutale          #+#    #+#             */
/*   Updated: 2024/11/04 19:33:12 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	if (!lst)
		return (0);
	while (lst != 0)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
/*  #include <stdio.h>

int main()

{
	char *str = " bonjour ";
	
	t_list *node = ft_lstnew(str);
	t_list *node2 = ft_lstnew(str);
	t_list *node3 = ft_lstnew(str);
	node->next = node2;
	node2->next = node3;
 	ft_lstsize(node);	 
	printf("%d", ft_lstsize(node));
	
	return (0);
}
 */