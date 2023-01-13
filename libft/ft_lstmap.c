/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waelhamd <waelhamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 13:08:30 by waelhamd          #+#    #+#             */
/*   Updated: 2021/11/17 21:14:32 by waelhamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*temp;

	newlist = NULL;
	while (lst != NULL)
	{
		temp = ft_lstnew (f (lst->content));
		if (!temp)
		{
			ft_lstclear (&newlist, del);
			return (NULL);
		}
		ft_lstadd_back (&newlist, temp);
		lst = lst->next;
	}
	return (newlist);
}
