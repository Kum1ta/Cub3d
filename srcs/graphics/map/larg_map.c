/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   larg_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:39:07 by edbernar          #+#    #+#             */
/*   Updated: 2024/03/15 23:08:49 by edbernar         ###   ########.fr       */
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

void	update_pos(t_mlx *mlx)
{
	static int	x = 0;
	static int	y = 0;
	int			diff1;
	int			diff2;

	if (mlx->mouse->pressed_left == true)
	{
		diff1 = mlx->mouse->x - x;
		diff2 = mlx->mouse->y - y;
		if (diff1 > 0)
			diff1 = 5;
		else if (diff1 < 0)
			diff1 = -5;
		if (diff2 > 0)
			diff2 = 5;
		else if (diff2 < 0)
			diff2 = -5;
		mlx->menu_map->x += diff1;
		mlx->menu_map->y += diff2;
		x = mlx->mouse->x;
		y = mlx->mouse->y;
	}
}

void	larg_map(t_mlx *mlx, int need_free)
{
	static void		*ptr[2] = {NULL, NULL};
	int				i;
	int				j;
	int				x;
	int				y;

	i = 0;
	// mlx_set_fps_goal(mlx->mlx, 60);
	if (ptr[0] || (ptr[0] && need_free))
		mlx_destroy_image(mlx->mlx, ptr[0]);
	if (ptr[1] || (ptr[1] && need_free))
		mlx_destroy_image(mlx->mlx, ptr[1]);
	if (need_free)
		return ;
	ptr[0] = creat_square(mlx, (int [2]){0, 0}, mlx->menu_map->size, 0xFFFFFF0F);
	ptr[1] = creat_square(mlx, (int [2]){0, 0}, mlx->menu_map->size / 2, 0xFFFF0000);
	y = 0;
	while (mlx->map->blocks[i] && y < HEIGHT)
	{
		j = 0;
		x = 0;
		while (mlx->map->blocks[i][j] != END && x < WIDTH)
		{
			x = j * mlx->menu_map->size + mlx->menu_map->x;
			y = i * mlx->menu_map->size + mlx->menu_map->y;
			if (mlx->map->blocks[i][j] == WALL)
				mlx_put_image_to_window(mlx->mlx, mlx->win, ptr[0], x, y);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, ptr[1], mlx->menu_map->x + mlx->menu_map->size * mlx->map->playerPos.x, mlx->menu_map->y + mlx->menu_map->size * mlx->map->playerPos.y);
}
