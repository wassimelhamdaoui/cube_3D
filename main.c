/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waelhamd <waelhamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 10:00:37 by waelhamd          #+#    #+#             */
/*   Updated: 2023/01/13 04:51:07 by waelhamd         ###   ########.fr       */
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
			color = (img->map[i][j] == '1') ?  0x326656: 0x000000;
			if(img->map[i][j] == ' ')
				color = 0x000000;
			draw_rectangle(img, j*TILE_SIZE, i*TILE_SIZE, color);
			j++;
		}
		i++;
	}
}

void	init_textures(t_data *img, t_elemts el)
{
	
	img->textures[0].texture_img = mlx_xpm_file_to_image(img->mlx, el.parse.no.path, &img->textures[0].width, &img->textures[0].height );
	img->textures[0].texture_addr = (int *)mlx_get_data_addr(img->textures[0].texture_img, &img->textures[0].bits_per_pixel, &img->textures[0].line_length, &img->textures[0].endian);
	
	img->textures[1].texture_img = mlx_xpm_file_to_image(img->mlx, el.parse.ea.path, &img->textures[1].width, &img->textures[1].height );
	img->textures[1].texture_addr = (int *)mlx_get_data_addr(img->textures[1].texture_img, &img->textures[1].bits_per_pixel, &img->textures[1].line_length, &img->textures[1].endian);

	img->textures[2].texture_img = mlx_xpm_file_to_image(img->mlx, el.parse.so.path, &img->textures[2].width, &img->textures[2].height );
	img->textures[2].texture_addr = (int *)mlx_get_data_addr(img->textures[2].texture_img, &img->textures[2].bits_per_pixel, &img->textures[2].line_length, &img->textures[2].endian);

	img->textures[3].texture_img = mlx_xpm_file_to_image(img->mlx, el.parse.we.path, &img->textures[3].width, &img->textures[3].height );
	img->textures[3].texture_addr = (int *)mlx_get_data_addr(img->textures[3].texture_img, &img->textures[3].bits_per_pixel, &img->textures[3].line_length, &img->textures[3].endian);

}

void	init_player(t_data *data, t_elemts el)
{
	
	data->player.x = (el.x * TILE_SIZE); // player cordonne x
	data->player.y = (el.y * TILE_SIZE); // player cordonne y
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
		
	data->player.moveSpeed = 3;
	data->player.rotationSpeed = 3 * (M_PI / 180);
	}

int	collision(double x, double y, char **map)
{
	int map_x;
	int map_y;
	
	map_x = x / TILE_SIZE;
	map_y = y / TILE_SIZE;

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
		
	ray->y_inter_h = floor(img->player.y/TILE_SIZE)*TILE_SIZE;
	if (ray->ray_dir_h == DOWN)
		ray->y_inter_h += TILE_SIZE;
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
		
	ray->x_inter_v =floor(img->player.x / TILE_SIZE)*TILE_SIZE;
	if(ray->ray_dir_v == RIGHT)
		ray->x_inter_v +=TILE_SIZE;

	ray->y_inter_v = img->player.y + (ray->x_inter_v - img->player.x) * tan(ray->ray_angle);
}

void step_horizontal(t_ray *ray)
{
	ray->y_step_h = TILE_SIZE;
	if(ray->ray_dir_h == UP)
		ray->y_step_h = -TILE_SIZE;
	ray->x_step_h = ray->y_step_h / tan(ray->ray_angle);
}

void step_vertical(t_ray *ray)
{
	ray->x_step_v = TILE_SIZE;
	if(ray->ray_dir_v == LEFT)
		ray->x_step_v = -TILE_SIZE;
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
		if(collision(x_touch, y_touch - y, img->map))
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
		if(collision(x_touch - x, y_touch, img->map))
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

void finding_project_wall(t_data *img, int id)
{
	double correct_d;
	int	texture_offset_x;
	int	texture_offset_y;

	correct_d = 0;
	img->rays[id].project_player_dist = ((WINDOW_WIDTH/2) / tan(30 * (M_PI/180)));
	if (img->rays[id].vertical_d > img->rays[id].horizontal_d)
	{
		correct_d = img->rays[id].horizontal_d * cos(img->rays[id].ray_angle - img->player.rotationAngel);
		img->rays[id].project_wall_height = img->rays[id].project_player_dist * TILE_SIZE / correct_d;
		// texture_offset_x = 
	}
	else
	{
		correct_d = img->rays[id].vertical_d * cos(img->rays[id].ray_angle - img->player.rotationAngel);
		img->rays[id].project_wall_height = img->rays[id].project_player_dist * TILE_SIZE / correct_d;
	}
	int i = (WINDOW_HEIGHT - img->rays[id].project_wall_height) / 2;
	int j = 0;
	while (j < i)
	{
		
		my_mlx_pixel_put(img, id, j, 0xfff000);
		j++;
	}
	while (i < img->rays[id].project_wall_height + ((WINDOW_HEIGHT - img->rays[id].project_wall_height) / 2))
	{
		my_mlx_pixel_put(img, id, i, 0xf11100);
		i++;
	}
	while (i < WINDOW_HEIGHT)
	{
		
		my_mlx_pixel_put(img, id, i, 0xffffFf);
		i++;
	}
}


void	create_field_of_view(t_data *img)
{
	int		id;
	double	rayangle;

	id = 0;
	rayangle = img->player.rotationAngel - (FOV_ANGLE / 2);
	while (id < NUM_RAYS)
	{
		img->rays[id].ray_angle = norm_angle(rayangle);
		//hadi kan7seb biha intersection horizontal
		find_horizontal_inter(img, &img->rays[id]);
		//hadi kan7seb biha intersection vertical
		find_vertical_inter(img, &img->rays[id]);
		//hadi kan7seb biha  distance mabin lwall ou player horizontal
		horizontal_distance(img, &img->rays[id]);
		//hadi kan7seb biha  distance mabin lwall ou player vertical
		vertical_distance(img, &img->rays[id]);
	
		// if(img->rays[id].vertical_d > img->rays[id].horizontal_d)
		// {
			// DDA(img->player.x, img->player.y, img->rays[id].x_hori_wall, img->rays[id].y_hori_wall , img,0xff0000);
			finding_project_wall(img, id);
		// }
		// else
		// {
		// 	finding_project_wall(img, id);
		// 	// DDA(img->player.x, img->player.y, img->rays[id].x_vert_wall, img->rays[id].y_vert_wall , img,0xff0000);
		// }
		// }		
		rayangle += FOV_ANGLE / NUM_RAYS;
		id++;
	}
}



void draw_player(t_data *img)
{
	double teta;
	int x;
	int y;
	int r = 0;
	// while(r <= img->player.radius)
	// {
	// 	teta = 0;
	// 	while (teta <= 360)
	// 	{
	// 		x =r*cos(teta *( M_PI / 180));
	// 		y =r*sin(teta * (M_PI / 180));
	// 		// printf("x = %d, y = %d\n", (int)(img->player.x), (int)(img->player.y));
	// 		my_mlx_pixel_put(img, img->player.x + x, img->player.y + y, 0xff0000);
	// 		teta+=1;
	// 	}
	// 	r+=1;
	// }
	create_field_of_view(img);
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
	return (0);
	
}

int key_handler(t_data *img)
{
	double new_x=0;
	double new_y=0;
	int move_step=0;
	if (img->player.turnDirection != 0)
	{
		img->player.rotationAngel += img->player.turnDirection * img->player.rotationSpeed;
		img->player.rotationAngel = norm_angle(img->player.rotationAngel);
	}
	else if (img->player.walkDirection != 0)
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
	else if(img->player.sideDirection != 0)
	{
		new_x = img->player.x + img->player.moveSpeed * cos(img->player.rotationAngel + ((M_PI / 2)*img->player.sideDirection));
		new_y = img->player.y + img->player.moveSpeed * sin(img->player.rotationAngel + ((M_PI /2)*img->player.sideDirection));
		if(collision(new_x ,new_y, img->map) == 0)
		{
			img->player.x =  new_x;
			img->player.y =  new_y;
		}
	}
	
	mlx_clear_window(img->mlx, img->mlx_win);
	img->img = mlx_new_image(img->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
								&img->endian);
	// map2D(img);
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
	init_textures(&img, el);
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

	
	
	int len = 0;
	// for (int i = 0; i < 360; i++)
	// {
	// 	for (int j = 0; j < 360; j++)
	// 	{
	// 		my_mlx_pixel_put(&img, j, i, img.textures[1].texture_addr[len]);
	// 		len++;
	// 	}
	// 	len++;
	// }

	mlx_put_image_to_window(img.mlx, img.mlx_win, img.img, 0, 0);

	
	mlx_hook(img.mlx_win, 2 ,1L<<0 ,key_pressed, &img);//key press hook
	mlx_hook(img.mlx_win,03 ,1L<<1 , key_release, &img);// key realas hook
	mlx_loop_hook(img.mlx, key_handler, &img);
	mlx_loop(img.mlx);
}