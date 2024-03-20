/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   larg_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:39:07 by edbernar          #+#    #+#             */
/*   Updated: 2024/03/20 21:57:54 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../graphics.h"

void	*creat_square(t_mlx *mlx, int size, int color)
{
	void	*img;
	int		i;
	int		j;

	img = mlx_new_image(mlx->mlx, size, size);
	if (!img)
		return (error_ptr("mlx_new_image() failed", NULL));
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (i < WIDTH && j < HEIGHT && i > 0 && j > 0)
				mlx_set_image_pixel(mlx->mlx, img, i, j, color);
			j++;
		}
		i++;
	}
	return (img);
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

void	print_map(t_mlx *mlx, void **ptr)
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
				mlx_put_image_to_window(mlx->mlx, mlx->win, ptr[0], x, y);
			j++;
		}
		mlx->menu_map->width = j * mlx->menu_map->size;
		i++;
	}
	mlx->menu_map->height = i * mlx->menu_map->size;
}

void	larg_map(t_mlx *mlx, int need_free)
{
	static void	*ptr[2] = {NULL, NULL};
	int			angle;

	if (ptr[0] || (ptr[0] && need_free))
		mlx_destroy_image(mlx->mlx, ptr[0]);
	if (ptr[1] || (ptr[1] && need_free))
		mlx_destroy_image(mlx->mlx, ptr[1]);
	if (need_free)
		return ;
	update_pos(mlx);
	ptr[0] = creat_square(mlx, mlx->menu_map->size + 1, 0xFFFFFF0F);
	ptr[1] = creat_square(mlx, mlx->menu_map->size / 2, 0xFFFF0000);
	angle = mlx->map->playerPos.h - 90;
	if (angle < 0)
		angle += 360;
	calculate_target_position(mlx, angle * (PI / 180.0),
		mlx->menu_map->size);
	print_map(mlx, ptr);
	mlx_put_image_to_window(mlx->mlx, mlx->win, ptr[1], mlx->menu_map->x
		+ mlx->menu_map->size * mlx->map->playerPos.x, mlx->menu_map->y
		+ mlx->menu_map->size * mlx->map->playerPos.y);
	mlx_string_put(mlx->mlx, mlx->win, WIDTH - 300, 40, 0xFFFFFFFF,
		"'tab' to return to the game");
	mlx_string_put(mlx->mlx, mlx->win, WIDTH - 300, 50, 0xFFFFFFFF,
		"'r' to reset the map");
}
