#include"cub3d.h"

int	ft_check_valid_n(char *str)
{
	int	i;
	int	number;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		i++;
	}
	number = ft_atoi(str);
	if (number < 0 || number > 255)
		return (-1);
	return (number);
}

int	ft_check_color(char *check, t_color *color)
{
	char	**data;
	int		a;
	int		b;
	int		c;

	data = ft_split(check, ',');
	if (twodlen(data) != 3)
		return (free2d(data), 0);
	color->a = ft_check_valid_n(data[0]);
	color->b = ft_check_valid_n(data[1]);
	color->c = ft_check_valid_n(data[2]);
	if (color->a == -1 || color->b == -1 || color->c == -1)
		return (free2d(data), 0);
	color->color = (color->a << 16) | (color->b << 8) | color->c;
	free2d(data);
	return (1);
}

char	**ft_realloc(char **map, char *line, int size)
{
	char	**tmp;
	int		i;

	tmp = (char **)malloc(sizeof(char *) * (size + 2));
	if (!tmp)
		return (free(tmp), NULL);
	i = 0;
	while (i < size)
	{
		tmp[i] = map[i];
		i++;
	}
	tmp[i++] = line;
	tmp[i] = NULL;
	free(map);
	return (tmp);
}

char	*to_low(char *ptr)
{
	int	i;

	while (ptr[i])
	{
		ptr[i] = ft_tolower(ptr[i]);
		i++;
	}
	return (ptr);
}

int	ft_check_acces(char *path)
{
	int	fd;
	int	len;

	fd = open(path, O_RDONLY, 777);
	if (fd == -1)
		return (0);
	close(fd);
	len = ft_strlen(path);
	if (len < 4 || ft_strcmp(to_low(path + (len - 4)), ".xpm"))
		return (0);
	return (1);
}
