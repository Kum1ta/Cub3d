/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   larg_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:39:07 by edbernar          #+#    #+#             */
/*   Updated: 2024/03/16 15:35:05 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../graphics.h"

void	*creat_square(t_mlx *mlx, int xy[2], int size, int color)
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
			if (xy[0] + i < WIDTH && xy[1] + j < HEIGHT && xy[0] + i > 0 && xy[1] + j > 0)
				mlx_set_image_pixel(mlx->mlx, img, xy[0] + i, xy[1] + j, color);
			j++;
		}
		i++;
	}
	return (img);
}

void update_pos(t_mlx *mlx)
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

void	larg_map(t_mlx *mlx, int need_free)
{
	static void		*ptr[2] = {NULL, NULL};
	int				i;
	int				j;
	int				x;
	int				y;

	i = 0;
	if (ptr[0] || (ptr[0] && need_free))
		mlx_destroy_image(mlx->mlx, ptr[0]);
	if (ptr[1] || (ptr[1] && need_free))
		mlx_destroy_image(mlx->mlx, ptr[1]);
	if (need_free)
		return ;
	update_pos(mlx);
	ptr[0] = creat_square(mlx, (int [2]){0, 0}, mlx->menu_map->size, 0xFFFFFF0F);
	ptr[1] = creat_square(mlx, (int [2]){0, 0}, mlx->menu_map->size / 2, 0xFFFF0000);
	y = 0;
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
	mlx_put_image_to_window(mlx->mlx, mlx->win, ptr[1], mlx->menu_map->x + mlx->menu_map->size * mlx->map->playerPos.x, mlx->menu_map->y + mlx->menu_map->size * mlx->map->playerPos.y);
	mlx_string_put(mlx->mlx, mlx->win, WIDTH - 300, 40, 0xFFFFFFFF, "'tab' to return to the game");
	mlx_string_put(mlx->mlx, mlx->win, WIDTH - 300, 50, 0xFFFFFFFF, "'r' to reset the map");
}
