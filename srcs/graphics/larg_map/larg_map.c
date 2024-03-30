/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   larg_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:39:07 by edbernar          #+#    #+#             */
/*   Updated: 2024/03/30 19:38:15 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../graphics.h"

void	draw_square(t_mlx *mlx, int size, int color, int x, int y)
{
	int		i;
	int		j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (x + i < WIDTH && y + j < HEIGHT && x + i > 0 && y + j > 0)
				mlx_pixel_put(mlx->mlx, mlx->win, x + i, y + j, color);
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

void	calculate_target_position(t_mlx *mlx, float angle, float distance)
{
	t_vec2	target_pos;

	target_pos.x = mlx->menu_map->x
		+ mlx->menu_map->size * mlx->map->playerPos.x
		+ mlx->menu_map->size / 4 + distance * cos(angle);
	target_pos.y = mlx->menu_map->y
		+ mlx->menu_map->size * mlx->map->playerPos.y
		+ mlx->menu_map->size / 4 + distance * sin(angle);
	mlx_pixel_put(mlx->mlx, mlx->win, target_pos.x, target_pos.y, 0xFFFF0000);
}

void	print_map(t_mlx *mlx)
{
	int				i;
	int				j;
	int				x;
	int				y;

	y = 0;
	i = 0;
	while (mlx->map->blocks[i] && y < HEIGHT)
	{
		j = 0;
		x = 0;
		while (mlx->map->blocks[i][j] != END && x <= WIDTH)
		{
			x = j * mlx->menu_map->size + mlx->menu_map->x;
			y = i * mlx->menu_map->size + mlx->menu_map->y;
			if (mlx->map->blocks[i][j] == WALL)
				draw_square(mlx, mlx->menu_map->size, 0x55F0000F, x, y);
			j++;
		}
		mlx->menu_map->width = j * mlx->menu_map->size;
		i++;
	}
	mlx->menu_map->height = i * mlx->menu_map->size;
	draw_square(mlx, 5, 0xFFFF0000, mlx->map->playerPos.x * mlx->menu_map->size + mlx->menu_map->x,
		mlx->map->playerPos.y * mlx->menu_map->size + mlx->menu_map->y);
}

void	larg_map(t_mlx *mlx, int need_free)
{
	int			angle;

	if (need_free)
		return ;
	update_pos(mlx);
	angle = mlx->map->playerPos.h - 90;
	if (angle < 0)
		angle += 360;
	calculate_target_position(mlx, angle * (PI / 180.0),
		mlx->menu_map->size);
	print_map(mlx);
	mlx_string_put(mlx->mlx, mlx->win, WIDTH - 300, 40, 0xFFFFFFFF,
		"'tab' to return to the game");
	mlx_string_put(mlx->mlx, mlx->win, WIDTH - 300, 50, 0xFFFFFFFF,
		"'r' to reset the map");
}
