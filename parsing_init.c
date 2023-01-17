#include"cub3d.h"

void	init_parse(t_parse *parse)
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

int	ft_longest_len(char **map, int *i)
{
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

char	*ft_add_spaces(char *str, int size)
{
	char	*line;
	int		len;

	line = malloc (sizeof(char) * size);
	if (!line)
		return (NULL);
	len = ft_strlen(str);
	ft_strlcpy(line, str, len + 1);
	while (len < size)
	{
		line[len] = ' ';
		len++;
	}
	line[len] = 0;
	return (line);
}

char	**create_matric(t_elemts *el)
{
	int		longest;
	int		size;
	char	**tmp;
	int		i;

	i = 0;
	longest = ft_longest_len(el->map, &size);
	tmp = (char **)malloc(sizeof(char *) * (size));
	if (!tmp)
		return (free2d(el->map), NULL);
	while (el->map[i])
	{
		tmp[i] = ft_add_spaces(el->map[i], longest);
		i++;
	}
	tmp[i] = NULL;
	free2d(el->map);
	el->map = tmp;
	return (tmp);
}

int	ft_readfile(char *path, t_elemts *elements)
{
	int			fd;
	char		*line;
	int			size;
	int			s;

	init_parse(&(elements->parse));
	fd = open(path, O_RDONLY, 777);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	elements->map = NULL;
	elements->elements = NULL;
	size = 0;
	s = 0;
	while (line)
	{
		if (map_line(line) && (line[0] != '\0' || size))
			elements->map = ft_realloc(elements->map, line, size++);
		else if (line[0] != '\0')
			elements->elements = ft_realloc(elements->elements, line, s++);
		else
			free(line);
		line = get_next_line(fd);
	}
	return (close(fd), 1);
}
