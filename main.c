/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waelhamd <waelhamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 10:00:37 by waelhamd          #+#    #+#             */
/*   Updated: 2022/12/31 16:27:22 by waelhamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3d.h"
#include<math.h>
#include<stdlib.h>
#include<stdio.h>


int	max(int a, int b)
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
			x += max(x1, x2);
		}
		if (error[1] < abs(x1 - x2))
		{
			error[0] += abs(x1 - x2);
			y += max(y1, y2);
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


void map2D(int map[10][10], t_data *img)
{
	int j;
	int i;
	int color;

	i = 0;
	while(i*TILE_SIZE < LINE*TILE_SIZE)
	{
		j = 0;
		while(j*TILE_SIZE < COLON*TILE_SIZE)
		{
			color = (map[i][j] == 1) ?  0x34A817: 0xffffff;
			draw_rectangle(img, j*TILE_SIZE, i*TILE_SIZE, color);
			j++;
		}
		i++;
	}
}


void	init_player(t_player *player)
{
	player->x = WINDOW_WIDTH / 2;
	player->y = WINDOW_HEIGHT / 2;
	player->radius = 5;
	player->turnDirection = 0;// -1 or 1
	player->walkDirection = 0;// -1 or 1
	player->rotationAngel = M_PI;
	player->moveSpeed = 5;
	player->rotationSpeed = 2 * (M_PI / 180);
}

int	collision(int x, int y)
{
	int map_x;
	int map_y;
	
	map_x = (int)round(x / TILE_SIZE);
	map_y = (int)round(y / TILE_SIZE);
	//printf("map_x:%d  \nmap_y:%d  \n", map_x, map_y);
	if (map[map_y][map_x] == 1)
		return 1;
	return 0;
}



void	create_field_of_view(t_player *player, t_data *img)
{
	int columnid;
	double rayangle;
	
	columnid = 0;
	rayangle = player->rotationAngel - (FOV_ANGLE / 2);
	while (rayangle <= player->rotationAngel + (FOV_ANGLE / 2))
	{
		bresenham(player->x, player->y, player->x + cos(rayangle) * 50, player->y + sin(rayangle) * 50, img,0xff0000);
		rayangle += FOV_ANGLE / NUM_RAYS;
	}
}



void draw_player(t_data *img, t_player *player)
{
	double teta;
	int x = player->x;
	int y = player->y;
	int new_x;
	int new_y;
	int r = 0;
	int move_step;


	move_step = player->walkDirection * player->moveSpeed;
	new_x = player->x + move_step * cos(player->rotationAngel);
	new_y = player->y + move_step * sin(player->rotationAngel);
	// printf("%d\n", collision(new_x, new_y));
	if (collision(new_x, new_y) == 0)
	{
		player->x = new_x;
		player->y = new_y; 
	}
	while(r <= player->radius)
	{
		teta = 0;
		while (teta <= 360)
		{
			x =r*cos(teta *( M_PI / 180));
			y =r*sin(teta * (M_PI / 180));
			// printf("x = %d, y = %d\n", (int)(player->x + x), (int)(player->y+y));
			my_mlx_pixel_put(img, player->x + x, player->y+y, 0xff0000);
			teta+=1;
		}
		r+=1;
	}
	player->rotationAngel += player->turnDirection * player->rotationSpeed;
	create_field_of_view(player, img);
}

void key_pressed(int keycode, t_data *img)
{
	int	new_x;
	int new_y;


	if(keycode == 125)
		img->player.walkDirection = -1;
	else if(keycode == 126)
		img->player.walkDirection = 1;
	else if(keycode == 0)
		img->player.turnDirection = -1;
	else if(keycode == 2)
		img->player.turnDirection = 1;
	else if(keycode == 123)
	{
		new_x = img->player.x + img->player.moveSpeed * cos(img->player.rotationAngel - M_PI / 2);
		new_y = img->player.y + img->player.moveSpeed * sin(img->player.rotationAngel - M_PI / 2);
		if(collision(new_x ,new_y) == 0)
		{
			img->player.x +=  img->player.moveSpeed * cos(img->player.rotationAngel - M_PI / 2);
			img->player.y +=  img->player.moveSpeed * sin(img->player.rotationAngel - M_PI / 2);
		}
	}
	else if(keycode == 124)
	{
		new_x = img->player.x + img->player.moveSpeed * cos(img->player.rotationAngel + M_PI / 2);
		new_y = img->player.y + img->player.moveSpeed * sin(img->player.rotationAngel + M_PI / 2);
		if(collision(new_x ,new_y) == 0)
		{
			img->player.x +=  img->player.moveSpeed * cos(img->player.rotationAngel + M_PI / 2);
			img->player.y +=  img->player.moveSpeed * sin(img->player.rotationAngel + M_PI / 2);
		}
	}
	
}

int key_handler(int keycode, t_data *img)
{

	key_pressed(keycode, img);
	if (keycode == 0 || keycode == 2)
	{
		mlx_clear_window(img->mlx, img->mlx_win);
		img->img = mlx_new_image(img->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
		img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
									&img->endian);
		map2D(map, img);
		draw_player(img, &img->player);
		mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
	}
	else if (keycode == 125 || keycode == 126)
	{
		mlx_clear_window(img->mlx, img->mlx_win);
		img->img = mlx_new_image(img->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
		img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
									&img->endian);
		map2D(map, img);
		draw_player(img, &img->player);
		mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
	}
	else if (keycode == 124 || keycode == 123)
	{
		mlx_clear_window(img->mlx, img->mlx_win);
		img->img = mlx_new_image(img->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
		img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
									&img->endian);
		map2D(map, img);
		draw_player(img, &img->player);
		mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
	}
	return 0;
}
int key_release(int keycode, t_data *img)
{
	if(keycode == 125)
		img->player.walkDirection = 0;
	else if(keycode == 126)
		img->player.walkDirection = 0;
	else if(keycode == 0)
		img->player.turnDirection = 0;
	else if(keycode == 2)
		img->player.turnDirection = 0;
		
	return 0;
}

int	main(void)
{

	t_data	img;

	img.mlx = mlx_init();
	img.mlx_win = mlx_new_window(img.mlx, WINDOW_HEIGHT, WINDOW_WIDTH, "Hello world!");
	img.img = mlx_new_image(img.mlx, WINDOW_HEIGHT, WINDOW_WIDTH);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	
	map2D(map, &img);
	init_player(&img.player);
	draw_player(&img, &img.player);
	
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
	mlx_hook(img.mlx_win, 2 ,1L<<0 ,key_handler, &img);//key press hook
	mlx_hook(img.mlx_win,03 ,1L<<1 , key_release, &img);// key realas hook
	// mlx_loop_hook(img.mlx, key_handler, &img);
	mlx_loop(img.mlx);
}