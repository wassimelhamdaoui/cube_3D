/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waelhamd <waelhamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:02:07 by waelhamd          #+#    #+#             */
/*   Updated: 2021/11/17 22:27:00 by waelhamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	len;
	size_t	k;

	i = 0;
	j = 0;
	len = 0;
	while (dst[i])
		i++;
	k = i;
	while (src[len])
		len++;
	if (i >= dstsize)
		return (len + dstsize);
	while ((dst[i] || src[j]) && i < dstsize - 1)
	{	
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (len + k);
}
