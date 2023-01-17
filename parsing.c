
#include"cub3d.h"

int	parse_map(char *path, t_elemts *el)
{
	if (!ft_readfile(path, el))
		return (0);
	if (ft_clone_el(el))
		return (free2d(el->map), free2d(el->elements), 0);
	create_matric(el);
	if (!ft_check_validmap(el))
		return (free2d(el->map), free2d(el->elements), 0);
	return (1);
}

t_elemts	parsing(int ac, char **av)
{
	t_elemts	el;

	if (ac != 2)
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
