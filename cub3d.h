/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waelhamd <waelhamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 10:00:58 by waelhamd          #+#    #+#             */
/*   Updated: 2023/01/17 21:51:48 by waelhamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H
#include "mlx.h"
#include <math.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include "./libft/libft.h"
#include "get_next_line.h"


# define LEFT_KEY 123
# define RIGHT_KEY 124
# define DOWN_KEY 125
# define UP_KEY 126
# define ESC_KEY 53
# define W 13
# define S 1
# define A 0
# define D 2
# define ESC 53

# define UP 1
# define DOWN 2
# define RIGHT 3
# define LEFT 4
# define MINI_WIDTH 100
# define MINI_HEIGHT 100
# define WINDOW_WIDTH 1000
# define WINDOW_HEIGHT 1000
# define FOV_ANGLE (60 * (M_PI / 180))
# define NUM_RAYS WINDOW_WIDTH


typedef struct	s_color
{
	int	on;
	int	a;
	int	b;
	int	c;
	int	color;
}				t_color;


typedef struct	s_side
{
	int		i;
	char	*path;
}	t_side;

typedef struct	s_parse
{
	t_side	no;
	t_side	so;
	t_side	we;
	t_side	ea;
	t_color	f;
	t_color	c;
}				t_parse;

typedef struct s_elements{
	char 	**map;
	char 	**elements;
	char 	p_player;
	int		x;
	int		y;
	t_parse parse;
}			t_elemts;

typedef struct	s_ray
{
	double	ray_angle;

	double	x_inter_h;
	double	y_inter_h;
	int		ray_dir_h;
	double	x_step_h;
	double	y_step_h;
	double	x_hori_wall;
	double	y_hori_wall;
	double	horizontal_d;
	
	double	vertical_d;
	double	x_vert_wall;
	double	y_vert_wall;
	double	x_step_v;
	double	y_step_v;
	double	x_inter_v;
	double	y_inter_v;
	int 	ray_dir_v;

	int		project_wall_height;
	double	project_player_dist;
}				t_ray;

typedef struct	s_player
{
	double	x;
	double	y;
	double	rotationAngel;// = M_PI /2
	char	p_player;
	int		radius;
	int		turnDirection; // have to value -1 or 1 to decide if i increase angel or decrease it
	int		walkDirection; // have two value -1 or 1 to decide if i want to move front or back
	int		sideDirection;
	int		moveSpeed;	// 3.0 or somting like that
	double	rotationSpeed;// 3* (M_PI / 180)
}				t_player;

typedef struct s_texture
{
	void	*texture_img;
	int		*texture_addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}		t_texture;


typedef struct	s_data 
{
	void		*mlx;
	void		*mlx_win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			line;
	int			colone;
	char		**map;
	t_parse		parse;
	t_ray		rays[1000];
	t_texture	textures[4];
	t_player	player;
}				t_data;

int			tile_size;

void		init_parse(t_parse *parse);
void		free2d(char **tab);
int			twodlen(char **check);
int			max(int a, int b);
int			ft_check_valid_n(char *str);
int			ft_check_color(char *check, t_color *color);
int			ft_check_acces(char *path);
int			is_valid(char c);
int			map_line(char *line);
int			ft_clone_xpm(t_side *s, char **data);
int			ft_clone_color(t_color *color, char **data);
int			ft_clone_el(t_elemts *el);
int			ft_longest_len(char **map, int *i);
int			vertical_check(char **map);
int			horizontal_check(char **map);
int			ft_check_player(t_elemts *el);
int			ft_isdigit(int c);
int			ft_check_validmap(t_elemts *el);
int			parse_map(char *path, t_elemts *el);
int			ft_isdigit(int c);
int			ft_strcmp(char *s1, char *s2);
char		**ft_realloc(char **map, char *line, int size);
char		*to_low(char *ptr);
char		*ft_add_spaces(char *str, int size);
char		**ft_split(char const *s, char c);
int			ft_readfile(char *path, t_elemts *elements);
t_elemts	parsing(int ac, char **av);
void	free2d(char **tab);
int		twodlen(char **check);
int		max(int a, int b);
int	ft_check_valid_n(char *str);
int	ft_check_color(char *check, t_color *color);
char	**ft_realloc(char **map, char *line, int size);
char	*to_low(char *ptr);
int	ft_check_acces(char *path);
char	**create_matric(t_elemts *el);

#endif