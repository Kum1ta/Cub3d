/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 18:27:58 by edbernar          #+#    #+#             */
/*   Updated: 2024/03/19 18:03:14 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raycasting.h"

void	put_health(t_mlx *mlx, void *img)
{
	int	x;
	int	y;
	int	max;

	y = 0;
	max = mlx->player->health * 349 / 100;
	while (y < 18)
	{
		x = 0;
		while (x < 349)
		{
			if (x < max)
				mlx_set_image_pixel(mlx->mlx, img, x + 1, y + 181, 0xFFC82626);
			else
				mlx_set_image_pixel(mlx->mlx, img, x + 1, y + 181, 0xFF000000);
			x++;
		}
		y++;
	}
}

void	draw_map(t_mlx *mlx, int need_free)
{
	static void	*ptr = NULL;
	// int			corner[4][2];
	int			i;
	int			j;
	int			x;
	int			y;

	y = 0;
	i = 0;
	if (ptr)
		mlx_destroy_image(mlx->mlx, ptr);
	if (need_free)
		return ;
	ptr = mlx_new_image(mlx->mlx, 350, 180);
	if (!ptr)
		return ;
	while (mlx->map->blocks[i] && y < 200)
	{
		j = 0;
		x = 0;
		while (mlx->map->blocks[i][j] != END && x <= 350)
		{
			x = j * 14;
			y = i * 14;
			// if (mlx->map->blocks[i][j] == WALL)
			// 	draw_polygon_4(mlx, ptr, corner, 0xFF000000);
			j++;
		}
		i++;
	}
}

void	mini_map(t_mlx *mlx, float angle[WIDTH], float distance[WIDTH], int need_free)
{
	(void)angle;
	(void)distance;
	static void		*img = NULL;
	static float	last_x = 0;
	static float	last_y = 0;
	int	x;
	int	y;

	if (need_free)
	{
		draw_map(mlx, 1);
		if (img)
			mlx_destroy_image(mlx->mlx, img);
		return ;
	}
	y = 0;
	if (last_x != mlx->map->playerPos.x || last_y != mlx->map->playerPos.y)
	{
		last_x = mlx->map->playerPos.x;
		last_y = mlx->map->playerPos.y;
		if (img)
			mlx_destroy_image(mlx->mlx, img);
		img = mlx_new_image(mlx->mlx, 351, 200);
	}
	else
	{
		draw_map(mlx, 0);
		mlx_put_image_to_window(mlx->mlx, mlx->win, img, 50, HEIGHT - 225);
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->textures->player_ico->img, 205, HEIGHT - 100);
		return ;
	}
	while (y < 200)
	{
		x = 0;
		mlx_set_image_pixel(mlx->mlx, img, x++, y, 0xF091a3b0);
		while (x < 350)
		{
			if (y == 199 || y == 0 || y == 180)
				mlx_set_image_pixel(mlx->mlx, img, x, y, 0xF091a3b0);
			else
				mlx_set_image_pixel(mlx->mlx, img, x, y, 0xF0343434);
			x++;
		}
		mlx_set_image_pixel(mlx->mlx, img, x, y, 0xF091a3b0);
		y++;
	}
	put_health(mlx, img);
	mlx_put_image_to_window(mlx->mlx, mlx->win, img, 50, HEIGHT - 225);
	draw_map(mlx, 0);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->textures->player_ico->img, 205, HEIGHT - 100);
}
