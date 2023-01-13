/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waelhamd <waelhamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 16:13:04 by waelhamd          #+#    #+#             */
/*   Updated: 2021/11/18 16:17:01 by waelhamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static void	recursive(long n, int fd)
{
	if (n <= 9)
		ft_putchar_fd(n + '0', fd);
	else
	{
		recursive(n / 10, fd);
		recursive(n % 10, fd);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	long	i;

	i = n;
	if (i < 0)
	{
		ft_putchar_fd('-', fd);
		i = i * -1;
		recursive(i, fd);
	}
	else
		recursive(i, fd);
}
