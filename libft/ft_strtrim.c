/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waelhamd <waelhamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 18:43:45 by waelhamd          #+#    #+#             */
/*   Updated: 2023/01/13 05:01:34 by waelhamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static size_t	ft_check(char s, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == s)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char *s1, char *set)
{
	int		i;
	int		j;
	int		k;
	char	*ptr;

	i = 0;
	k = 0;
	if (!s1 || !set)
		return (NULL);
	j = ft_strlen(s1) - 1;
	while (ft_check(s1[i], set) == 1)
		i++;
	while (j >= i && ft_check(s1[j], set) == 1)
		j--;
	ptr = (char *)malloc(sizeof(char) * (j - i + 2));
	if (!ptr)
		return (NULL);
	while (i <= j)
	{
		ptr[k] = s1[i];
		i++;
		k++;
	}
	ptr[k] = '\0';
	return (free(s1), ptr);
}
