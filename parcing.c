/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waelhamd <waelhamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 16:40:49 by waelhamd          #+#    #+#             */
/*   Updated: 2022/12/31 18:24:55 by waelhamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3d.h"
#include <fcntl.h>
#include<stdio.h>

int numofcolon(char* name)
{
	int i = 0;
	int fd;
	fd=open(name,O_RDONLY,777);
	char *line = get_next_line(fd);
	while(line)
	{
		line = get_next_line(fd);
		i++;
	}
	close(fd);
	return i;
}
char **create_matric(char *name)
{
	int fd;
	int i = 0;
	int numofline;

	numofline = numofcolon(name);
	fd=open(name,O_RDONLY,777);
	if(fd < 0)
		return 0;
	char **matrice;
	matrice= (char **)malloc(sizeof(char *) * numofline);
	char *line = get_next_line(fd);
	while(line && i < numofline)
	{
		matrice[i] = line;
		
		line = get_next_line(fd);
		i++;
	}
	close(fd);
	return matrice;
}

int main(int ac, char **av)
{
	char **matrice;

	matrice = create_matric(av[1]);

	for(int j = 0; j < numofcolon(av[1]);j++)
	{
		printf("%s\n",matrice[j]);
	}
}