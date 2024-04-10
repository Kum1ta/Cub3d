/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   larg_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:39:07 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/10 20:35:30 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../graphics.h"

void	draw_square(t_mlx *mlx, int size, int color, int x, int y, void *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (x + i >= 0 && x + i < mlx->stg->width && y + j >= 0 && y + j < mlx->stg->height)
				mlx_set_image_pixel(mlx->mlx, img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	update_pos(t_mlx *mlx)
{
	int	dx;
	int	dy;

	if (mlx->mouse->pressed_left)
	{
		dx = mlx->mouse->x - mlx->mouse->last_x;
		dy = mlx->mouse->y - mlx->mouse->last_y;
		mlx->menu_map->x += dx;
		mlx->menu_map->y += dy;
	}
	mlx->mouse->last_x = mlx->mouse->x;
	mlx->mouse->last_y = mlx->mouse->y;
}


void	fill_img_map(t_mlx *mlx, void *img)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	y = mlx->menu_map->y;
	while (i < mlx->map->height)
	{
		j = 0;
		x = mlx->menu_map->x;
		while (mlx->map->blocks[i][j].type != END)
		{
			if (mlx->map->blocks[i][j].type == WALL)
				draw_square(mlx, mlx->menu_map->size, 0xFF646464, x - 5, y - 5, img);
			else if (mlx->map->blocks[i][j].type == DOOR)
				draw_square(mlx, mlx->menu_map->size, 0xFF989898, x - 5, y - 5, img);
			else if (mlx->map->blocks[i][j].type == FLOOR)
				draw_square(mlx, mlx->menu_map->size, 0xFF323232, x, y, img);
			x += mlx->menu_map->size;
			j++;
		}
		y += mlx->menu_map->size;
		i++;
	}
}

void	fill_image(t_mlx *mlx, void *img, int color, int xy[2])
{
	int	i;
	int	j;

	i = 0;
	while (i < xy[0])
	{
		j = 0;
		while (j < xy[1])
		{
			mlx_set_image_pixel(mlx->mlx, img, i, j, color);
			j++;
		}
		i++;
	}
}


void	down_bar(t_mlx *mlx, int need_free)
{
	static void	*img = NULL;

	if (need_free)
	{
		if (img)
			mlx_destroy_image(mlx->mlx, img);
		return ;
	}
	if (!img)
	{
		img = mlx_new_image(mlx->mlx, mlx->stg->width, 100);
		fill_image(mlx, img, 0xFF212121, (int [2]){mlx->stg->width, 100});
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, img, 0, mlx->stg->height - 100);
}

void	larg_map(t_mlx *mlx, int need_free)
{
	static void	*img = NULL;

	if (need_free)
	{
		down_bar(mlx, 1);
		if (img)
			mlx_destroy_image(mlx->mlx, img);
		return ;
	}
	if (img)
	{
		mlx_destroy_image(mlx->mlx, img);
		img = NULL;
	}
	if (!img)
		img = mlx_new_image(mlx->mlx, mlx->stg->width, mlx->stg->height);
	update_pos(mlx);
	fill_img_map(mlx, img);
	mlx_put_image_to_window(mlx->mlx, mlx->win, img, 0, 0);
	mlx_string_put(mlx->mlx, mlx->win, 10, 50, 0xFFFFFFFF,
		"'tab' to return to the game");
	mlx_string_put(mlx->mlx, mlx->win, 10, 80, 0xFFFFFFFF,
		"'r' to reset the map");
	down_bar(mlx, 0);
	mlx_string_put(mlx->mlx, mlx->win, 50, mlx->stg->height - 40, 0xFFFFFFFF, "Resume");
}
