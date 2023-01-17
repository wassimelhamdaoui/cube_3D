#include"cub3d.h"

int	is_valid(char c)
{
	if (c != '0' && c != '1' && c != ' ' && c != 'N'
		&& c != 'S' && c != 'E' && c != 'W')
		return (0);
	return (1);
}

int	vertical_check(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] != 0)
		{
			if (map[i][j] == ' ' && map[i + 1] != NULL
				&& (map[i + 1][j] == '0'))
				return (0);
			if (map[i][j] == '0' && (map[i + 1] == NULL
				|| map[i + 1][j] == ' ' || i == 0))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	horizontal_check(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == ' ' && map[i][j + 1] == '0')
				return (0);
			if (map[i][j] == '0' && (map[i][j + 1] == ' '
				|| map[i][j + 1] == '\0' || j == 0))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_check_player(t_elemts *el)
{
	int	i;
	int	j;

	i = 0;
	while (el->map[i])
	{
		j = 0;
		while (el->map[i][j])
		{
			if (el->map[i][j] == 'E' || el->map[i][j] == 'S'
					|| el->map[i][j] == 'W' || el->map[i][j] == 'N')
			{
				if (el->p_player)
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
	if (!ft_check_player(el) || el->x == -1
		|| !horizontal_check(el->map) || !vertical_check(el->map))
		return (0);
	return (1);
}
