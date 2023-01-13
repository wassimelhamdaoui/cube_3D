/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waelhamd <waelhamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 15:07:47 by waelhamd          #+#    #+#             */
/*   Updated: 2021/11/18 15:55:47 by waelhamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	ft_intlen(long n)
{
	int	i;
	int	j;

	i = 1;
	j = n;
	if (n < 0)
		n = n * -1;
	while (i > 0 && n > 0)
	{
		n = n / 10;
		i++;
	}
	if (j <= 0)
		return (i);
	return (i - 1);
}

char	*ft_itoa(int n)
{
	int		i;
	long	nb;
	char	*ptr;
	int		check;

	check = 0;
	nb = n;
	i = ft_intlen(nb);
	ptr = (char *) malloc (sizeof(char) * i + 1);
	if (ptr == NULL)
		return (NULL);
	if (nb < 0)
	{
		check = 1;
		nb = nb * -1;
		ptr[0] = '-';
	}
	while (--i >= check)
	{	
		ptr[i] = nb % 10 + 48;
		nb = nb / 10;
	}
	ptr[ft_intlen(n)] = '\0';
	return (ptr);
}
