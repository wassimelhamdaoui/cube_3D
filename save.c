/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waelhamd <waelhamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 10:00:37 by waelhamd          #+#    #+#             */
/*   Updated: 2023/01/10 21:20:20 by waelhamd         ###   ########.fr       */
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

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	if (x > 0 && x < WINDOW_WIDTH && y > 0 && y < WINDOW_HEIGHT)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

void	bresenham(int x1,int y1,int x2, int y2, t_data *img, int color)
{
	int	x;
	int	y;
	int	error[2];

	error[0] = abs (x1 - x2) - abs(y1 - y2);
	x = x1;
	y = y1;
	while (x != x2 || y != y2)
	{
		my_mlx_pixel_put(img, x, y, color);
		error[1] = error[0] * 2;
		if (error[1] > -abs(y1 - y2))
		{
			error[0] -= abs(y1 - y2);
			x += max1(x1, x2);
		}
		if (error[1] < abs(x1 - x2))
		{
			error[0] += abs(x1 - x2);
			y += max1(y1, y2);
		}
	}
}

void draw_rectangle(t_data *img, int x, int y, int color)
{
	int ax_x;
	int ax_y;
	int i = y;
	ax_x = x +TILE_SIZE;
	ax_y = y+TILE_SIZE;
	while(x <= ax_x)
	{
		y = i;
		while(y <= ax_y)
		{
			if(y%TILE_SIZE == 0 || x%TILE_SIZE == 0)
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
	while(i*TILE_SIZE < img->line * TILE_SIZE)
	{
		j = 0;
		while(j*TILE_SIZE < img->colone * TILE_SIZE)
		{
			color = (img->map[i][j] == '1') ?  0x34A817: 0xffffff;
			if(img->map[i][j] == ' ')
				color = 0x000000;
			draw_rectangle(img, j*TILE_SIZE, i*TILE_SIZE, color);
			j++;
		}
		i++;
	}
}


void	init_player(t_data *data, t_elemts el)
{
	
	data->player.x = (el.x * TILE_SIZE) + TILE_SIZE / 2; // player cordonne x
	data->player.y = (el.y * TILE_SIZE) + TILE_SIZE / 2; // player cordonne y
	data->player.p_player = el.p_player; // player possition
	data->map = el.map;
	 data->colone = ft_strlen(el.map[0]);
	 data->line = twodlen(el.map);

	data->player.radius = 5;
	data->player.turnDirection = 0;// -1 or 1
	data->player.walkDirection = 0;// -1 or 1
	data->player.sideDirection = 0;
	if (el.p_player == 'N')
		data->player.rotationAngel = 3*M_PI/2;
	else if(el.p_player == 'S')
		data->player.rotationAngel = M_PI/2;
	else if(el.p_player == 'E')
		data->player.rotationAngel = 0;
	else if(el.p_player == 'W')
		data->player.rotationAngel = M_PI;
		
	data->player.moveSpeed = 2;
	data->player.rotationSpeed = 2 * (M_PI / 180);
}

int	collision(int x, int y, char **map)
{
	int map_x;
	int map_y;
	
	map_x = (int)round(x / TILE_SIZE);
	map_y = (int)round(y / TILE_SIZE);
	//printf("map_x:%d  \nmap_y:%d  \n", map_x, map_y);
	if (map[map_y][map_x] == '1')
		return 1;
	return 0;
}

// int finding_step(int new_y, t_data *img, int rayangle)
// {
// 	int i;
// 	int old_map_y;
// 	int old_y;

// 	i = 0;
// 	old_y = new_y;
// 	old_map_y = round(new_y / TILE_SIZE);
// 	while (old_map_y == round(new_y / TILE_SIZE))
// 	{
				
// 		new_y = new_y + sin(rayangle) * i;
// 		i++;
// 		if (old_map_y != round(new_y / TILE_SIZE))
// 			return (old_y - new_y);
// 	}
// 	return(0);
// }

// int	finding_first_intersec(t_data *img, double rayangle)
// {
// 	int i;
// 	int old_map_y;
// 	int new_y;

// 	i=0;
// 	old_map_y = round(img->player.y / TILE_SIZE);
// 	while (old_map_y == round(img->player.y / TILE_SIZE))
// 	{
				
// 		new_y = img->player.y + sin(rayangle) * i;
// 		i++;
// 		old_map_y = round(new_y / TILE_SIZE);
// 	}
// 	return (finding_step(new_y, img, rayangle));
// }

void find_horizontal_inter(t_data *img, t_ray *ray)
{
	double	yside;
	double	xside;
	if (ray->ray_angle > M_PI)
		ray->ray_dir_h = UP;
	else if (ray->ray_angle <= M_PI)
		ray->ray_dir_h = DOWN;
	ray->y_inter_h = (img->player.y/TILE_SIZE);
	ray->y_inter_h *= TILE_SIZE;
	if (ray->ray_dir_h == DOWN)
		ray->y_inter_h += TILE_SIZE;
	yside = img->player.y - ray->y_inter_h;
	xside = yside/tan(ray->ray_angle);
	ray->x_inter_h = xside + img->player.x;
}

void	create_field_of_view(t_data *img)
{
	int		id;
	double	rayangle;
	int inter_x;
	int inter_y;

	
	id = 0;
	rayangle = img->player.rotationAngel - (FOV_ANGLE / 2);
	// while (rayangle <= img->player.rotationAngel + (FOV_ANGLE / 2))
	// {
		// int a = finding_first_intersec(img, rayangle);
		// if (rayangle >= 4.711419 && rayangle <= 4.713389)
		// {
		// 	rayangle += (FOV_ANGLE / NUM_RAYS)+10;
		// 	printf("hoho\n");
		// }
		img->rays[id].ray_angle = rayangle;
		// printf("rayangle %lf\n", rayangle);
		// find_horizontal_inter(img, &img->rays[id]);
		// bresenham(img->player.x, img->player.y, img->rays[id].x_inter_h, img->rays[id].y_inter_h, img,0xff0000);
		bresenham(img->player.x, img->player.y, img->player.x + cos(img->player.rotationAngel) * 50, img->player.y + sin(img->player.rotationAngel) * 50, img,0xff0000);
		rayangle += FOV_ANGLE / NUM_RAYS;
		id++;
	// }
}



void draw_player(t_data *img)
{
	double teta;
	int x;
	int y;
	int r = 0;
	while(r <= img->player.radius)
	{
		teta = 0;
		while (teta <= 360)
		{
			x =r*cos(teta *( M_PI / 180));
			y =r*sin(teta * (M_PI / 180));
			// printf("x = %d, y = %d\n", (int)(img->player.x), (int)(img->player.y));
			my_mlx_pixel_put(img, img->player.x + x, img->player.y + y, 0xff0000);
			teta+=1;
		}
		r+=1;
	}
	create_field_of_view(img);
}

int key_pressed(int keycode, t_data *img)
{
	if(keycode == S)
		img->player.walkDirection = -1;
	else if(keycode == W)
		img->player.walkDirection = 1;
	else if(keycode == RIGHT_KEY)
		img->player.turnDirection = -1;
	else if(keycode == LEFT_KEY)
		img->player.turnDirection = 1;
	else if (keycode == A)
		img->player.sideDirection = -1;
	else if (keycode == D)
		img->player.sideDirection = 1;
	return (0);
	// else if(keycode == A)
	// {
	// 	new_x = img->player.x + img->player.moveSpeed * cos(img->player.rotationAngel - M_PI / 2);
	// 	new_y = img->player.y + img->player.moveSpeed * sin(img->player.rotationAngel - M_PI / 2);
	// 	if(collision(new_x ,new_y, img->map) == 0)
	// 	{
	// 		img->player.x +=  img->player.moveSpeed * cos(img->player.rotationAngel - M_PI / 2);
	// 		img->player.y +=  img->player.moveSpeed * sin(img->player.rotationAngel - M_PI / 2);
	// 	}
	// }
	// else if(keycode == D)
	// {
	// 	new_x = img->player.x + img->player.moveSpeed * cos(img->player.rotationAngel + M_PI / 2);
	// 	new_y = img->player.y + img->player.moveSpeed * sin(img->player.rotationAngel + M_PI / 2);
	// 	if(collision(new_x ,new_y, img->map) == 0)
	// 	{
	// 		img->player.x +=  img->player.moveSpeed * cos(img->player.rotationAngel + M_PI / 2);
	// 		img->player.y +=  img->player.moveSpeed * sin(img->player.rotationAngel + M_PI / 2);
	// 	}
	// }
	
}

int key_handler(t_data *img)
{
	int new_x=0;
	int new_y=0;
	int move_step=0;
	if (img->player.turnDirection != 0)
	{
		//calcule teta
		img->player.rotationAngel += img->player.turnDirection * img->player.rotationSpeed;
		//check if rotation < 0 || > 2pi(min twsal 2pi redha l 0) 
	}
	if (img->player.walkDirection != 0)
	{
		move_step = img->player.walkDirection * img->player.moveSpeed;
		new_x = img->player.x + move_step * cos(img->player.rotationAngel);
		new_y = img->player.y + move_step * sin(img->player.rotationAngel);
		
		if (collision(new_x, new_y, img->map) == 0)
		{
			img->player.x = new_x;
			img->player.y = new_y; 
		}
	}
	if(img->player.sideDirection != 0)
	{
		
		new_x = img->player.x + img->player.moveSpeed * cos((img->player.rotationAngel + (M_PI / 2))*img->player.sideDirection);
		new_y = img->player.y + img->player.moveSpeed * sin((img->player.rotationAngel + (M_PI / 2))*img->player.sideDirection);
		if(collision(new_x ,new_y, img->map) == 0)
		{
			img->player.x +=  img->player.moveSpeed * cos((img->player.rotationAngel +(M_PI / 2))*img->player.sideDirection);
			img->player.y +=  img->player.moveSpeed * sin((img->player.rotationAngel + (M_PI / 2))*img->player.sideDirection);
		}
	}
	mlx_clear_window(img->mlx, img->mlx_win);
	img->img = mlx_new_image(img->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
								&img->endian);
	map2D(img);
	draw_player(img);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
	return 0;
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
	t_elemts el;

	img.mlx = mlx_init();
	img.mlx_win = mlx_new_window(img.mlx, WINDOW_HEIGHT, WINDOW_WIDTH, "Hello world!");
	img.img = mlx_new_image(img.mlx, WINDOW_HEIGHT, WINDOW_WIDTH);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	el = parsing(ac, av);
	init_player(&img, el);
	map2D(&img);
	draw_player(&img);
	
	/*
	player movement :
	(x,y)
	radius;
	turn_direction
	walk_direction
	rotational_Angel
	move_speed = 3 like example it mean the number of pixels which i need to translat
	rotation_speed = is the angel which i need to rotate the player
	*/

	mlx_put_image_to_window(img.mlx, img.mlx_win, img.img, 0, 0);
	mlx_hook(img.mlx_win, 2 ,1L<<0 ,key_pressed, &img);//key press hook
	mlx_hook(img.mlx_win,03 ,1L<<1 , key_release, &img);// key realas hook
	mlx_loop_hook(img.mlx, key_handler, &img);
	mlx_loop(img.mlx);
}