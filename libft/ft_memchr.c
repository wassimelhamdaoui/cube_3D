/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waelhamd <waelhamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 19:11:24 by waelhamd          #+#    #+#             */
/*   Updated: 2021/11/17 21:21:24 by waelhamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*casts;
	unsigned char	newc;
	size_t			i;

	i = 0;
	casts = (unsigned char *)s;
	newc = (unsigned char)c;
	while (i < n)
	{
		if (casts[i] == newc)
			return (&casts[i]);
		i++;
	}
	return (0);
}
