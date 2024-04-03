/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 18:27:58 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/03 14:11:43 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raycasting.h"

void	put_health(t_mlx *mlx)
{
	float	health;
	int		x;
	int		y;

	y = 181 + POS_MINI_MAP_Y;
	health = 350 * mlx->player->health / 100;
	while (y < 199 + POS_MINI_MAP_Y)
	{
		x = 0 + POS_MINI_MAP_X + 1;
		while (x < 350 + POS_MINI_MAP_X && x < health + POS_MINI_MAP_X + 1)
		{
			mlx_pixel_put(mlx->mlx, mlx->win, x, y, 0xFFD93A3A);
			x++;
		}
		y++;
	}
}

void	draw_player_pos(t_mlx *mlx)
{
	int	x;
	int	y;

	y = POS_MINI_MAP_Y + 90 - 2;
	while (y < POS_MINI_MAP_Y + 90 + 2)
	{
		x = POS_MINI_MAP_X + 175 - 2;
		while (x < POS_MINI_MAP_X + 175 + 2)
		{
			mlx_pixel_put(mlx->mlx, mlx->win, x, y, 0xFF0000FF);
			x++;
		}
		y++;
	}
	
}

void	print_square(t_mlx *mlx, int x, int y)
{
	float	x_calc;
	float	y_calc;
	int		x_map;
	int		y_map;

	y_map = -1;
	while (++y_map < WALL_SIZE_MINI_MAP - 1)
	{
		x_calc = (POS_MINI_MAP_X + 150) + ((x - mlx->map->playerPos.x) * WALL_SIZE_MINI_MAP);
		y_calc = (POS_MINI_MAP_Y + 82.5) + ((y - mlx->map->playerPos.y) * WALL_SIZE_MINI_MAP);
		x_map = -1;
		while (++x_map < WALL_SIZE_MINI_MAP - 1 && y_calc + y_map < POS_MINI_MAP_Y + 180
			&& y_calc + y_map > POS_MINI_MAP_Y + 1 && x_calc + x_map < POS_MINI_MAP_X + 350)
		{
			if (x_calc + x_map > POS_MINI_MAP_X + 1)
				mlx_pixel_put(mlx->mlx, mlx->win, x_calc + x_map, y_calc + y_map, 0xFF534B4B);
		}
	}
}

void	draw_map(t_mlx *mlx)
{
	int	x;
	int	y;

	y = -1;
	while (++y < mlx->menu_map->height / mlx->menu_map->size)
	{
		x = -1;
		while (++x < mlx->menu_map->width / mlx->menu_map->size)
		{
			if (mlx->map->blocks[y][x].type == WALL)
				print_square(mlx, x, y);
		}
	}
	draw_player_pos(mlx);
}

void	mini_map(t_mlx *mlx)
{
	int	x;
	int	y;

	y = 0 + POS_MINI_MAP_Y;
	while (y < 200 + POS_MINI_MAP_Y && y < HEIGHT)
	{
		x = 0 + POS_MINI_MAP_X;
		mlx_pixel_put(mlx->mlx, mlx->win, x++, y, 0xF091a3b0);
		while (x < 350 + POS_MINI_MAP_X && x < WIDTH)
		{
			if (y == 199 + POS_MINI_MAP_Y || y == 0 + POS_MINI_MAP_Y || y == 180 + POS_MINI_MAP_Y)
				mlx_pixel_put(mlx->mlx, mlx->win, x, y, 0xF091a3b0);
			else
				mlx_pixel_put(mlx->mlx, mlx->win, x, y, 0xF0343434);
			x++;
		}
		mlx_pixel_put(mlx->mlx, mlx->win, x, y, 0xF091a3b0);
		y++;
	}
	put_health(mlx);
	draw_map(mlx);
}
