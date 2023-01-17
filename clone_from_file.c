#include"cub3d.h"

int	map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
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
		return (free2d(data), 0);
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
		return (0);
	return (1);
}

int	ft_clone_el(t_elemts *el)
{
	int		i;
	char	**data;

	i = -1;
	while (el->elements[++i])
	{
		data = ft_split(el->elements[i], ' ');
		if (twodlen(data) == 2 && ft_strcmp(data[0], "NO") == 0
			&& ft_clone_xpm(&el->parse.no, data));
		else if (twodlen(data) == 2 && ft_strcmp(data[0], "SO") == 0
			&& ft_clone_xpm(&el->parse.so, data));
		else if (twodlen(data) == 2 && ft_strcmp(data[0], "WE") == 0
			&& ft_clone_xpm(&el->parse.we, data));
		else if (twodlen(data) == 2 && ft_strcmp(data[0], "EA") == 0
			&& ft_clone_xpm(&el->parse.ea, data));
		else if (twodlen(data) == 2 && ft_strcmp(data[0], "F") == 0
			&& ft_clone_color(&el->parse.f, data))
			free2d(data);
		else if (twodlen(data) == 2 && ft_strcmp(data[0], "C") == 0
			&& ft_clone_color(&el->parse.c, data))
			free2d(data);
		else
			return (free2d(data), 1);
	}
	return (0);
}
