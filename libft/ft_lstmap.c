/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboutale <aboutale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:56:07 by aboutale          #+#    #+#             */
/*   Updated: 2024/11/06 20:35:29 by aboutale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*templst;
	void	*newcontent;

	if (lst == NULL || del == NULL || f == NULL)
		return (NULL);
	templst = NULL;
	newlst = NULL;
	while (lst != NULL)
	{
		newcontent = f(lst->content);
		templst = ft_lstnew(newcontent);
		if (templst == NULL)
		{
			del(newcontent);
			ft_lstclear(&newlst, del);
			return (NULL);
		}
		ft_lstadd_back(&newlst, templst);
		lst = lst->next;
	}
	return (newlst);
}

/* void *ft_test(void *c)
{
	char *str = (char *)c;
	str[0] = 'W';
	return str;

} */
/* void	*ft_tolowerslst(void *c)
{
	
	int i = 0;
	char *str = (char *)c;
	char *new_str = malloc(strlen(str) + 1);
    if (!new_str)
		return (NULL);

	while (str[i] != '\0')
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			new_str[i] =str[i] + 32;
		i++;
	}
	new_str[i] = '\0';
	return new_str;
} */
/*  void del(void *content)
{
    free(content);
}
#include <stdio.h>
int main()
{
	char *str = "BONJOUR";
	char *str2 = "SALUT";
	char *str3 = "CAVA";
	
	t_list *node1;
	t_list *node2;
	t_list *node3;
	t_list *final;

	node1 = ft_lstnew(str);
	node2 = ft_lstnew(str2);
	node3 = ft_lstnew(str3);
	
	node1->next = node2;
	node2->next = node3;

	final = ft_lstmap(node1, ft_test, del);
	while (final != NULL)
	{
		printf("%s\n",(char *)final->content );
		final = final->next;
	}
	return 0;
}  */
