/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waelhamd <waelhamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 10:00:58 by waelhamd          #+#    #+#             */
/*   Updated: 2022/12/08 17:35:03 by waelhamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H
#include"mlx.h"

#define TILE_SIZE 50
#define LINE 10
#define COLON 10
#define WINDOW_WIDTH COLON * TILE_SIZE
#define WINDOW_HEIGHT LINE * TILE_SIZE
#define FOV_ANGLE 60 * (M_PI / 180)
#define NUM_RAYS 320


int map[LINE][COLON] = {
		{1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,1,0,0,0,1,1,0,1},
		{1,1,1,1,0,0,0,1,0,1},
		{1,0,0,0,0,0,0,1,0,1},
		{1,0,0,0,0,0,0,1,0,1},
		{1,1,1,1,0,0,0,1,0,1},
		{1,0,0,0,0,0,0,1,1,1},
		{1,1,1,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1},
	};

typedef struct	s_player
{
	int x;
	int y;
	int radius;
	int turnDirection; // have to value -1 or 1 to decide if i increase angel or decrease it
	int walkDirection; // have two value -1 or 1 to decide if i want to move front or back
	double rotationAngel;// = M_PI /2
	int moveSpeed;	// 3.0 or somting like that
	double rotationSpeed;// 3* (M_PI / 180)
}				t_player;

typedef struct	s_data 
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_player player;
}				t_data;
//rayangle += FOV_ANGLE / NUNRAYS;
#endif