/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waelhamd <waelhamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 19:24:50 by waelhamd          #+#    #+#             */
/*   Updated: 2021/11/17 21:24:04 by waelhamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*newdst;
	char	*newsrc;
	size_t	i;

	i = 0;
	newdst = (char *)dst;
	newsrc = (char *)src;
	if (!dst && !src)
		return (NULL);
	if (newdst > newsrc)
	{
		while (len > 0)
		{
			newdst[len - 1] = newsrc[len - 1];
			len--;
		}
	}
	while (i < len)
	{
		newdst[i] = newsrc[i];
		i++;
	}
	return (dst);
}
