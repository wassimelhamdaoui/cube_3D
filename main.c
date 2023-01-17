/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waelhamd <waelhamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 10:00:37 by waelhamd          #+#    #+#             */
/*   Updated: 2023/01/17 22:01:55 by waelhamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3d.h"
#include<math.h>
#include<stdlib.h>
#include<stdio.h>


int	max1(int a, int b)
{
	if (a < b)
		return (1);
	else
		return (-1);
}
double  norm_angle(double angle)
{
    if (angle >= 0)
		angle = fmod(angle, (2 * M_PI));
	else
		angle += (2 * M_PI);
        return(angle);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	if (x > 0 && x < WINDOW_WIDTH && y > 0 && y < WINDOW_HEIGHT)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}
 

void draw_rectangle(t_data *img, int x, int y, int color)
{
	int ax_x;
	int ax_y;
	int i = y;
	ax_x = x +tile_size;
	ax_y = y+tile_size;
	while(x <= ax_x)
	{
		y = i;
		while(y <= ax_y)
		{
			if(y%tile_size == 0 || x%tile_size == 0)
				my_mlx_pixel_put(img, x, y, 0x000000);
			else
			my_mlx_pixel_put(img, x, y, color);
			y++;
		}
		x++;
	}
}

void map2D(t_data *img)
{
	int j;
	int i;
	int color;

	i = 0;
	while(i*tile_size < img->line * tile_size)
	{
		j = 0;
		while(j*tile_size < img->colone * tile_size)
		{
			color = (img->map[i][j] == '1') ?  0x326656: 0x000000;
			if(img->map[i][j] == ' ')
				color = 0x000000;
			draw_rectangle(img, j*tile_size, i*tile_size, color);
			j++;
		}
		i++;
	}
}

void	init_textures(t_data *img, t_elemts el)
{
	img->textures[0].texture_img = mlx_xpm_file_to_image(img->mlx, el.parse.no.path, &img->textures[0].width, &img->textures[0].height);
	img->textures[0].texture_addr = (int *)mlx_get_data_addr(img->textures[0].texture_img, &img->textures[0].bits_per_pixel, &img->textures[0].line_length, &img->textures[0].endian);
	
	img->textures[1].texture_img = mlx_xpm_file_to_image(img->mlx, el.parse.ea.path, &img->textures[1].width, &img->textures[1].height);
	img->textures[1].texture_addr = (int *)mlx_get_data_addr(img->textures[1].texture_img, &img->textures[1].bits_per_pixel, &img->textures[1].line_length, &img->textures[1].endian);

	img->textures[2].texture_img = mlx_xpm_file_to_image(img->mlx, el.parse.so.path, &img->textures[2].width, &img->textures[2].height);
	img->textures[2].texture_addr = (int *)mlx_get_data_addr(img->textures[2].texture_img, &img->textures[2].bits_per_pixel, &img->textures[2].line_length, &img->textures[2].endian);

	img->textures[3].texture_img = mlx_xpm_file_to_image(img->mlx, el.parse.we.path, &img->textures[3].width, &img->textures[3].height);
	img->textures[3].texture_addr = (int *)mlx_get_data_addr(img->textures[3].texture_img, &img->textures[3].bits_per_pixel, &img->textures[3].line_length, &img->textures[3].endian);
}

void	init_player(t_data *data, t_elemts el)
{
	
	data->colone = ft_strlen(el.map[0]);
	data->line = twodlen(el.map);
	if(data->colone <= data->line)
		tile_size = WINDOW_WIDTH/data->colone;
	else
		tile_size = WINDOW_HEIGHT/data->line;
	data->player.moveSpeed = 3;
	data->player.rotationSpeed = 3 * (M_PI / 180);
	data->player.x = (el.x * tile_size) + tile_size/2;
	data->player.y = (el.y * tile_size) + tile_size/2;
	data->player.p_player = el.p_player;
	data->map = el.map;
	data->parse = el.parse;
	data->player.radius = 5;
	if (el.p_player == 'N')
		data->player.rotationAngel = 3*M_PI/2;
	else if(el.p_player == 'S')
		data->player.rotationAngel = M_PI/2;
	else if(el.p_player == 'E')
		data->player.rotationAngel = 0;
	else if(el.p_player == 'W')
		data->player.rotationAngel = M_PI;
}

int	collision(double x, double y, char **map, t_data *data)
{
	int map_x;
	int map_y;
	
	map_x = x / tile_size;
	map_y = y / tile_size;
	
	if (map[map_y][map_x] == '1')
		return 1;
	else if (map[map_y][(int)(data->player.x /tile_size)] == '1' && map[(int)(data->player.y / tile_size)][map_x] == '1')
        return 1;
	
	return 0;
}

int	collision_ray(double x, double y, char **map, t_data *data)
{
	int map_x;
	int map_y;
	
	map_x = x / tile_size;
	map_y = y / tile_size;
	
	if (map[map_y][map_x] == '1')
		return 1;
	return 0;
}

void find_horizontal_inter(t_data *img, t_ray *ray)
{
	double	yside;
	double	xside;
	if (ray->ray_angle > M_PI)
		ray->ray_dir_h = UP;
	else if (ray->ray_angle <= M_PI)
		ray->ray_dir_h = DOWN;
		
	ray->y_inter_h = floor(img->player.y/tile_size)*tile_size;
	if (ray->ray_dir_h == DOWN)
		ray->y_inter_h += tile_size;
	yside = ray->y_inter_h - img->player.y ;
	xside = yside/tan(ray->ray_angle);
	ray->x_inter_h = img->player.x + xside;
}

void find_vertical_inter(t_data *img, t_ray *ray)
{
	double	yside;
	double	xside;

	if(ray->ray_angle > 3*M_PI/2 || ray->ray_angle <= M_PI/2)
		ray->ray_dir_v = RIGHT;
	else
		ray->ray_dir_v = LEFT;
		
	ray->x_inter_v =floor(img->player.x / tile_size)*tile_size;
	if(ray->ray_dir_v == RIGHT)
		ray->x_inter_v +=tile_size;

	ray->y_inter_v = img->player.y + (ray->x_inter_v - img->player.x) * tan(ray->ray_angle);
}

void step_horizontal(t_ray *ray)
{
	ray->y_step_h = tile_size;
	if(ray->ray_dir_h == UP)
		ray->y_step_h = -tile_size;
	ray->x_step_h = ray->y_step_h / tan(ray->ray_angle);
}

void step_vertical(t_ray *ray)
{
	ray->x_step_v = tile_size;
	if(ray->ray_dir_v == LEFT)
		ray->x_step_v = -tile_size;
	ray->y_step_v = ray->x_step_v * tan(ray->ray_angle);
}

double	ecliden_distance(double x0, double x1, double y0, double y1)
{
	double d;

	d = sqrt(pow((x1 - x0),2)+ pow((y1 - y0),2));
	return (d);
}

void	horizontal_distance(t_data *img, t_ray *ray)
{
	double x_touch;
	double y_touch;
	int y = 0;

	x_touch = ray->x_inter_h;
	y_touch = ray->y_inter_h;
	if(ray->ray_dir_h == UP)
		y = 1;
	ray->horizontal_d = MAXFLOAT;
	ray->y_hori_wall = MAXFLOAT;
	ray->x_hori_wall = MAXFLOAT;
	step_horizontal(ray);
	while(x_touch >= 0 && x_touch < WINDOW_WIDTH && y_touch >= 0 && y_touch < WINDOW_HEIGHT)
	{
		if(collision_ray(x_touch, y_touch - y, img->map, img))
		{
			ray->horizontal_d = ecliden_distance(img->player.x, x_touch, img->player.y , y_touch);
			ray->x_hori_wall = x_touch;
			ray->y_hori_wall = y_touch;
			break;
		}
		else
		{
			x_touch+=ray->x_step_h;
			y_touch+=ray->y_step_h;
		}
	}
}

void	vertical_distance(t_data *img, t_ray *ray)
{
	double x_touch;
	double y_touch;
	int x = 0;

	x_touch = ray->x_inter_v;
	y_touch = ray->y_inter_v;
	if(ray->ray_dir_v == LEFT)
		x = 1;
	ray->vertical_d = MAXFLOAT;
	ray->y_vert_wall = MAXFLOAT;
	ray->x_vert_wall = MAXFLOAT;
	step_vertical(ray);
	while(x_touch >=0 && x_touch < WINDOW_WIDTH && y_touch >= 0 && y_touch < WINDOW_HEIGHT)
	{
		if(collision_ray(x_touch - x, y_touch, img->map, img))
		{
			ray->vertical_d = ecliden_distance(img->player.x, x_touch, img->player.y , y_touch);
			ray->x_vert_wall = x_touch;
			ray->y_vert_wall = y_touch;
			break;
		}
		else
		{
			x_touch+=ray->x_step_v;
			y_touch+=ray->y_step_v;
		}
	}
}

void DDA(double X0, double Y0, double X1, double Y1, t_data *data ,int col)
{
    // calculate dx & dy
    double dx = X1 - X0;
    double dy = Y1 - Y0;

    // calculate steps required for generating pixels
    double steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
 
    // calculate increment in x & y for each steps
    double Xinc = (double)(dx / steps);
    double Yinc = (double)(dy / steps);
 
    // Put pixel for each step
    double X = X0;
    double Y = Y0;
    for (int i = 0; i <= steps; i++) {
        my_mlx_pixel_put(data, X, Y, 0xf11100); 
        X += Xinc;
        Y += Yinc;
    }
}

int	check_text(t_data *img, int id)
{
	if (img->rays[id].ray_angle > 0 && img->rays[id].ray_angle <= M_PI_2)
	{
		if (img->rays[id].vertical_d > img->rays[id].horizontal_d)
			return(2);
		else
			return(1);
	}
	else if (img->rays[id].ray_angle > M_PI_2 && img->rays[id].ray_angle <= M_PI)
	{
		if (img->rays[id].vertical_d > img->rays[id].horizontal_d)
			return(2);
		else
			return(3);
	}
	else if (img->rays[id].ray_angle > M_PI && img->rays[id].ray_angle <= (3 * M_PI / 2))
	{
		if (img->rays[id].vertical_d > img->rays[id].horizontal_d)
			return(0);
		else
			return(3);
	}
	else
	{
		if (img->rays[id].vertical_d > img->rays[id].horizontal_d)
			return(0);
		else
			return(1);
	}
	return(0);
}



void rendring(t_data *img, int id, int	texture_offset_x)
{
	int	texture_offset_y;
	int distance_from_top;
	int i ;
	int j;

	i = ((WINDOW_HEIGHT - img->rays[id].project_wall_height) / 2) + 1;
	j = 0;
	while (j <= i)
	{
		my_mlx_pixel_put(img, id, j, img->parse.c.color);
		j++;
	}
	while (i < img->rays[id].project_wall_height + ((WINDOW_HEIGHT - img->rays[id].project_wall_height) / 2))
	{
		distance_from_top = i + (img->rays[id].project_wall_height/2 - WINDOW_HEIGHT/2);
		texture_offset_y = distance_from_top * ((float)img->textures->height / img->rays[id].project_wall_height);
		my_mlx_pixel_put(img, id, i, img->textures[check_text(img, id)].texture_addr[(img->textures->width * texture_offset_y) + texture_offset_x]);
		i++;
	}
	while (i < WINDOW_HEIGHT)
	{
		my_mlx_pixel_put(img, id, i, img->parse.f.color);
		i++;
	}
}

void finding_project_wall(t_data *img, int id)
{
	double correct_d;
	int	texture_offset_x;
	int distance_from_top;

	correct_d = 0;
	img->rays[id].project_player_dist = ((WINDOW_WIDTH/2) / tan(30 * (M_PI/180)));
	if (img->rays[id].vertical_d > img->rays[id].horizontal_d)
	{
		correct_d = img->rays[id].horizontal_d * cos(img->rays[id].ray_angle - img->player.rotationAngel);
		img->rays[id].project_wall_height = img->rays[id].project_player_dist * tile_size / correct_d;
		texture_offset_x = (img->rays[id].x_hori_wall / tile_size - (int)img->rays[id].x_hori_wall / tile_size) * img->textures->width;
		rendring(img, id, texture_offset_x);
	}
	else
	{
		correct_d = img->rays[id].vertical_d * cos(img->rays[id].ray_angle - img->player.rotationAngel);
		img->rays[id].project_wall_height = img->rays[id].project_player_dist * tile_size / correct_d;
		texture_offset_x = (img->rays[id].y_vert_wall / tile_size - (int)img->rays[id].y_vert_wall / tile_size) * img->textures->width;
		rendring(img, id, texture_offset_x);
	}
}


void	start_game(t_data *img)
{
	int		id;
	double	rayangle;

	id = 0;
	rayangle = img->player.rotationAngel - (FOV_ANGLE / 2);
	while (id < NUM_RAYS)
	{
		img->rays[id].ray_angle = norm_angle(rayangle);
		find_horizontal_inter(img, &img->rays[id]);
		find_vertical_inter(img, &img->rays[id]);
		horizontal_distance(img, &img->rays[id]);
		vertical_distance(img, &img->rays[id]);
		finding_project_wall(img, id);	
		rayangle += FOV_ANGLE / NUM_RAYS;
		id++;
	}
}

int key_pressed(int keycode, t_data *img)
{
	if(keycode == S)
		img->player.walkDirection = -1;
	else if(keycode == W)
		img->player.walkDirection = 1;
	else if(keycode == RIGHT_KEY)
		img->player.turnDirection = 1;
	else if(keycode == LEFT_KEY)
		img->player.turnDirection = -1;
	else if (keycode == A)
		img->player.sideDirection = -1;
	else if (keycode == D)
		img->player.sideDirection = 1;
	else if(keycode == ESC)
		exit(0);
	return (0);
	
}

void	turndirection(t_data *img)
{
	img->player.rotationAngel += img->player.turnDirection * img->player.rotationSpeed;
	img->player.rotationAngel = norm_angle(img->player.rotationAngel);
}

void	walkdirection(t_data *img)
{
	double new_x;
	double new_y;
	int move_step;

	move_step = img->player.walkDirection * img->player.moveSpeed;
	new_x = img->player.x + move_step * cos(img->player.rotationAngel);
	new_y = img->player.y + move_step * sin(img->player.rotationAngel);
	if (collision(new_x, new_y, img->map, img) == 0)
	{
		img->player.x = new_x;
		img->player.y = new_y; 
	}
}

void	sidedirection(t_data *img)
{
	double new_x;
	double new_y;

	new_x = img->player.x + img->player.moveSpeed * cos(img->player.rotationAngel + ((M_PI / 2)*img->player.sideDirection));
	new_y = img->player.y + img->player.moveSpeed * sin(img->player.rotationAngel + ((M_PI /2)*img->player.sideDirection));
	if(collision(new_x ,new_y, img->map, img) == 0)
	{
		img->player.x =  new_x;
		img->player.y =  new_y;
	}
}

int key_handler(t_data *img)
{
	
	if (img->player.turnDirection != 0)
		turndirection(img);
	else if (img->player.walkDirection != 0)
		walkdirection(img);
	else if(img->player.sideDirection != 0)
		sidedirection(img);
	mlx_destroy_image(img->mlx, img->img);
	mlx_clear_window(img->mlx, img->mlx_win);
	img->img = mlx_new_image(img->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
								&img->endian);
	map2D(img);
	start_game(img);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
	return (0);
}

int key_release(int keycode, t_data *img)
{
	if(keycode == W)
		img->player.walkDirection = 0;
	else if(keycode == S)
		img->player.walkDirection = 0;
	else if(keycode == RIGHT_KEY)
		img->player.turnDirection = 0;
	else if(keycode == LEFT_KEY)
		img->player.turnDirection = 0;
	else if (keycode == A)
		img->player.sideDirection = 0;
	else if (keycode == D)
		img->player.sideDirection = 0;
	return 0;
}



int	main(int ac, char **av)
{

	t_data	img;
	t_data mini;
	t_elemts el;

	img.mlx = mlx_init();
	img.mlx_win = mlx_new_window(img.mlx, WINDOW_HEIGHT, WINDOW_WIDTH, "Hello world!");
	img.img = mlx_new_image(img.mlx, WINDOW_HEIGHT, WINDOW_WIDTH);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	el = parsing(ac, av);
	
	init_player(&img, el);
	init_textures(&img, el);
	start_game(&img);

	mlx_put_image_to_window(img.mlx, img.mlx_win, img.img, 0, 0);
	
	mlx_hook(img.mlx_win, 2 ,1L<<0 ,key_pressed, &img);//key press hook
	mlx_hook(img.mlx_win,03 ,1L<<1 , key_release, &img);// key realas hook
	mlx_loop_hook(img.mlx, key_handler, &img);
	mlx_loop(img.mlx);
	
}