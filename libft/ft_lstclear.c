/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waelhamd <waelhamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 13:52:13 by waelhamd          #+#    #+#             */
/*   Updated: 2021/11/17 21:14:09 by waelhamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*newnode;
	t_list	*head;

	head = *lst;
	while (head != NULL)
	{
		newnode = head->next;
		del (head->content);
		free (head);
		head = newnode;
	}
	*lst = NULL;
}
