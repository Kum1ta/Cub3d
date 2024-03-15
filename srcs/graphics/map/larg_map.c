/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   larg_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:39:07 by edbernar          #+#    #+#             */
/*   Updated: 2024/03/15 16:29:24 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../graphics.h"

void	draw_square(t_mlx *mlx, int xy[2], int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (xy[0] + i < WIDTH && xy[1] + j < HEIGHT && xy[0] + i > 0 && xy[1] + j > 0)
				mlx_set_image_pixel(mlx->mlx, mlx->img, xy[0] + i, xy[1] + j, color);
			j++;
		}
		i++;
	}
}

void	draw_rect(t_mlx *mlx, int xy[2], int size[2], int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size[1])
	{
		j = 0;
		while (j < size[0])
		{
			if (xy[0] + j < WIDTH && xy[1] + i < HEIGHT && xy[0] + j > 0 && xy[1] + i > 0)
				mlx_set_image_pixel(mlx->mlx, mlx->img, xy[0] + j, xy[1] + i, color);
			j++;
		}
		i++;
	}
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

int		change_icon_size(t_mlx *mlx, int *size)
{
	if (*size == mlx->menu_map->size)
		return (0);
	*size = mlx->menu_map->size;
	return (0);
}

void	larg_map(t_mlx *mlx)
{
	static int		last_size = 0;
	int				i;
	int				j;
	int				x;
	int				y;

	i = 0;
	printf("%f %f\n", mlx->map->playerPos.x * (float)mlx->menu_map->size, mlx->map->playerPos.y * (float)mlx->menu_map->size);
	if (mlx->img)
		mlx_destroy_image(mlx->mlx, mlx->img);
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	update_pos(mlx);
	if (change_icon_size(mlx, &last_size))
		return ;
	while (mlx->map->blocks[i])
	{
		j = 0;
		while (mlx->map->blocks[i][j] != END)
		{
			x = j * mlx->menu_map->size + mlx->menu_map->x;
			y = i * mlx->menu_map->size + mlx->menu_map->y;
			if (mlx->map->blocks[i][j] == WALL)
				draw_square(mlx, (int [2]){x, y}, mlx->menu_map->size, 0xFFFFFF0F);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}
