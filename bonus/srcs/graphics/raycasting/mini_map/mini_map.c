/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 18:27:58 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/15 17:02:49 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raycasting.h"

void	put_health(t_mlx *mlx)
{
	float	health;
	int		x;
	int		y;

	y = 181 + mlx->stg->minimap_pos_y;
	health = 350 * mlx->player->health / 100;
	while (y < 199 + mlx->stg->minimap_pos_y)
	{
		x = 0 + mlx->stg->minimap_pos_x + 1;
		while (x < 350 + mlx->stg->minimap_pos_x && x < health + mlx->stg->minimap_pos_x + 1)
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

	y = mlx->stg->minimap_pos_y + 90 - 2;
	while (y < mlx->stg->minimap_pos_y + 90 + 2)
	{
		x = mlx->stg->minimap_pos_x + 175 - 2;
		while (x < mlx->stg->minimap_pos_x + 175 + 2)
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
	while (++y_map < 20 - 1)
	{
		x_calc = (mlx->stg->minimap_pos_x + 155) + ((x - mlx->map->playerPos.x) * 20);
		y_calc = (mlx->stg->minimap_pos_y + 91) + ((y - mlx->map->playerPos.y) * 20);
		x_map = -1;
		while (++x_map < 20 - 1 && y_calc + y_map < mlx->stg->minimap_pos_y + 180
			&& y_calc + y_map > mlx->stg->minimap_pos_y + 1 && x_calc + x_map < mlx->stg->minimap_pos_x + 350)
		{
			if (x_calc + x_map > mlx->stg->minimap_pos_x + 1)
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
				print_square(mlx, x + 1 , y);
		}
	}
	draw_player_pos(mlx);
}

void	mini_map(t_mlx *mlx)
{
	int	x;
	int	y;

	y = 0 + mlx->stg->minimap_pos_y;
	while (y < 200 + mlx->stg->minimap_pos_y && y < mlx->stg->height)
	{
		x = 0 + mlx->stg->minimap_pos_x;
		mlx_pixel_put(mlx->mlx, mlx->win, x++, y, 0xF091a3b0);
		while (x < 350 + mlx->stg->minimap_pos_x && x <  mlx->stg->width)
		{
			if (y == 199 + mlx->stg->minimap_pos_y || y == 0 + mlx->stg->minimap_pos_y || y == 180 + mlx->stg->minimap_pos_y)
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
