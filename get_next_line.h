/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waelhamd <waelhamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 14:33:18 by waelhamd          #+#    #+#             */
/*   Updated: 2022/02/19 14:33:29 by waelhamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 1000000
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include<stdlib.h>
# include <fcntl.h>

char	*get_next_line(int fd);
int		get_ft_strlen(char	*str);
char	*get_ft_strdup(char *str);
char	*get_ft_strchr(char *s, int c);
char	*get_ft_strjoin(char *s1, char *s2);
#endif