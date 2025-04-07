/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <aboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:38:24 by aboutale          #+#    #+#             */
/*   Updated: 2024/12/13 19:31:58 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*newlist;

	newlist = (t_list *)malloc(sizeof(t_list));
	if (!newlist)
		return (NULL);
	newlist ->content = content;
	newlist->next = NULL;
	return (newlist);
}
/*
#include <stdio.h>
int main() {
    
    char *str = "Hello, World!";
    
    
    t_list *node = ft_lstnew(str);
    
    
    if (node == NULL) 
    {
        printf("Échec de la création du nœud.\n");
        return 1; 
    }

    
    printf("Contenu du nœud : %s\n", (char *)node->content);
    free(node);
    
    return 0;
}
 */