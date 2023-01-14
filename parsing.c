/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waelhamd <waelhamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 16:40:49 by waelhamd          #+#    #+#             */
/*   Updated: 2023/01/14 18:56:01 by waelhamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3d.h"
#include <fcntl.h>
#include<stdio.h>
#include <sys/stat.h>

/*************************************************************************************************/

void init_parse(t_parse *parse)
{
	parse->no.i = 0;
	parse->so.i = 0;
	parse->we.i = 0;
	parse->ea.i = 0;
	parse->c.on = 0;
	parse->f.on = 0;
	parse->so.path = NULL;
	parse->we.path = NULL;
	parse->ea.path = NULL;
	parse->no.path = NULL;
}

void free2d(char **tab)
{
	int i;

	i = 0;
	while(tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}


int twodlen(char **check)
{
	int i =0;
	while(check[i])
		i++;
	return i;
}

int	max(int a, int b)
{
	if (a < b)
		return (b);
	else
		return (a);
}



int	ft_check_valid_n(char *str)
{
	int i;
	int number;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return(-1);
		i++;
	}
	number = ft_atoi(str);
	if (number < 0 || number > 255)
		return (-1);
	return(number);
}

int ft_check_color(char *check, t_color *color)
{
	char **data;
	int a;
	int b;
	int c;

	data = ft_split(check, ',');
	if (twodlen(data) != 3)
		return(free2d(data), 0);
	color->a = ft_check_valid_n(data[0]);
	color->b = ft_check_valid_n(data[1]);
	color->c = ft_check_valid_n(data[2]);
	if(color->a == -1 ||  color->b == -1 || color->c == -1)
		return(free2d(data), 0);
	color->color = 
	free2d(data);
	return(1);
}

char **ft_realloc(char **map, char *line, int size){
	char **tmp;
	int	i;

	tmp = (char **)malloc(sizeof(char *) * (size + 2));
	i = 0;
	while (i < size){
		tmp[i] = map[i];
		i++;
	}
	tmp[i++] = line;
	tmp[i] = NULL;
	free(map);
	return (tmp);
}

char *to_low(char *ptr)
{
	int i;

	while (ptr[i])
	{
		ptr[i] = ft_tolower(ptr[i]);
		i++;
	}
	return (ptr);
}

int ft_check_acces(char *path)
{
	int fd;
	int len;

	fd = open(path,O_RDONLY,777);
	if(fd == -1)
		return 0;
	close(fd);	
	len = ft_strlen(path);
	if (len < 4 || ft_strcmp(to_low(path + (len - 4)), ".xpm"))
		return (0);
	return 1;
}

int is_valid(char c){
	if (c != '0' && c != '1' && c != ' ' && c != 'N' && c != 'S' && c != 'E' && c != 'W')
		return (0);
	return (1);
}

int	map_line(char *line)
{
	int i;

	i = 0;
	while (line[i]){
		if (!is_valid(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_clone_xpm(t_side *s, char **data)
{

	if (!s->i)
	{
		s->i = 1;
		if (ft_check_acces(data[1]))
			s->path = data[1];
		else
			return (0);
	}
	else
		return(free2d(data), 0);
	free(data[0]);
	free(data);
	return (1);
}

int	ft_clone_color(t_color *color, char **data)
{
	if (!color->on)
	{
		color->on = 1;
		if (!ft_check_color(data[1], color))
			return (0);
	}
	else
		return(0);
	return (1);
}

int	ft_clone_el(t_elemts *el)
{
	int i = 0;
	char **data;

	while (el->elements[i])
	{
		data = ft_split(el->elements[i],' ');
		// printf("%s\n", data[0]);
		// if (ft_strcmp(data[0], "F") == 0){
		// 	int j = ft_clone_color(&el->parse.f, data);
		// 	printf("%d\n", j);
		// }
		if (twodlen(data) == 2 && ft_strcmp(data[0], "NO") == 0 && ft_clone_xpm(&el->parse.no, data))
			;
		else if (twodlen(data) == 2 && ft_strcmp(data[0], "SO") == 0 && ft_clone_xpm(&el->parse.so, data))
			;
		else if (twodlen(data) == 2 && ft_strcmp(data[0], "WE") == 0 && ft_clone_xpm(&el->parse.we, data))
			;
		else if (twodlen(data) == 2 && ft_strcmp(data[0], "EA") == 0 && ft_clone_xpm(&el->parse.ea, data))
			;
		else if (twodlen(data) == 2 && ft_strcmp(data[0], "F") == 0 && ft_clone_color(&el->parse.f, data))
			free2d(data);
		else if (twodlen(data) == 2 && ft_strcmp(data[0], "C") == 0 && ft_clone_color(&el->parse.c, data))
			free2d(data);
		else
			return (free2d(data), 1);
		i++;
	}
	return (0);
}

int	ft_longest_len(char **map, int *i){
	int	len;

	*i = 0;
	len = 0;
	while (map[*i])
	{
		len = max(len, ft_strlen(map[*i]));
		(*i)++;
	}
	return (len);
}

char	*ft_add_spaces(char *str, int size){
	char	*line;
	int		len;

	line = malloc(sizeof(char) * size);
	if (!line)
		return (NULL);
	len = ft_strlen(str);
	ft_strlcpy(line, str, len + 1);
	while (len < size){
		line[len] = ' ';
		len++;
	}
	line[len] = 0;
	return (line);
}
int vertical_check(char **map)
{
    int i = 0;
    int j = 0;

    while (map[i])
    {
        j = 0;
        while(map[i][j] != 0)
        {
            if (map[i][j] == ' ' && map[i + 1] != NULL && (map[i + 1][j] == '0'))
                return (0);
            if (map[i][j] == '0' && (map[i + 1] == NULL || map[i + 1][j] == ' ' || i == 0))
                return (0);
            j++;
        }
        i++;
    }
    return (1);
}

int horizontal_check(char **map)
{
    int    i;
    int    j;

    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == ' ' && map[i][j + 1] == '0')
                return (0);
            if (map[i][j] == '0' && (map[i][j + 1] == ' ' || map[i][j + 1] == '\0' || j == 0))
                return (0);
            j++;
        }
        i++;
    }
    return (1);
}


int	ft_check_player(t_elemts *el)
{
	int i;
	int j;

	i = 0;
	while (el->map[i])
	{
		j = 0;
		while (el->map[i][j])
		{
			if (el->map[i][j] == 'E' || el->map[i][j] == 'S'
					|| el->map[i][j] == 'W' || el->map[i][j] == 'N')
			{
				if(el->p_player)
					return (printf("there's more player\n"), 0);
				el->p_player = el->map[i][j];
				el->x = j;
				el->y = i;
				el->map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_check_validmap(t_elemts *el)
{
	el->x = -1;
	if (!ft_check_player(el) || el->x == -1 || !horizontal_check(el->map) || !vertical_check(el->map))
		return 0;
	return 1;
}

char **create_matric(t_elemts *el)
{
	int		longest;
	int		size;
	char	**tmp;
	int		i;

	i = 0;
	longest = ft_longest_len(el->map, &size);
	tmp = (char **)malloc(sizeof(char *) * (size));
	while (el->map[i]){
		tmp[i] = ft_add_spaces(el->map[i], longest);
		i++;
	}
	tmp[i] = NULL;
	free2d(el->map);
	el->map = tmp;
	return (tmp);
}

t_elemts ft_readfile(char *path){
	int 		fd;
	char		*line;
	t_elemts	elements;
	int	size;
	int s;
	
	init_parse(&elements.parse);
	fd = open(path,O_RDONLY,777);
	line = get_next_line(fd);
	elements.map = NULL;
	elements.elements = NULL;
	size = 0;
	s = 0;
	while (line)
	{
		if (map_line(line) && (line[0] != '\0' || size))
			elements.map = ft_realloc(elements.map, line, size++);
		else if (line[0] != '\0')
			elements.elements = ft_realloc(elements.elements, line, s++);
		else
			free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (elements);
}

int parse_map(char *path, t_elemts *el)
{
	*el = ft_readfile(path);
	if (ft_clone_el(el))
		return (free2d(el->map), free2d(el->elements), 0);
	create_matric(el);
	if (!ft_check_validmap(el))
		return (free2d(el->map), free2d(el->elements), 0);
	return (1);
}

t_elemts parsing(int ac, char **av)
{
	t_elemts el;

	if(ac != 2)
	{
		printf("to few argument\n");
		exit(1);
	}
	if (!parse_map(av[1], &el))
	{
		printf("map invalid\n");
		exit(1);
	}
	free2d(el.elements);
	return (el);
}
