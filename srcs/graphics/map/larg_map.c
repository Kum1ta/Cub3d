/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   larg_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:39:07 by edbernar          #+#    #+#             */
/*   Updated: 2024/03/14 19:17:18 by edbernar         ###   ########.fr       */
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

void	update_pos(t_mlx *mlx)
{
	static int	x = 0;
	// static int	y = 0;
	int			diff;
	
	//probleme de positionnement
	if (mlx->mouse->pressed_left == true)
	{
		diff = mlx->mouse->x - x;
		mlx->menu_map->x = diff;
		printf("diff = %d\n", diff);
		// mlx->menu_map->y = mlx->menu_map->y + (mlx->mouse->y);
		x = mlx->menu_map->x;
		// y = mlx->menu_map->y;
		// (void)x;
		// (void)y;
	}
}

void	larg_map(t_mlx *mlx)
{
	int				i;
	int				j;
	int				x;
	int				y;

	i = 0;
	if (mlx->img)
		mlx_destroy_image(mlx->mlx, mlx->img);
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	update_pos(mlx);
	while (mlx->map->blocks[i])
	{
		j = 0;
		x = 0;
		while (mlx->map->blocks[i][j] != END)
		{
			x = j * mlx->menu_map->size;
			y = i * mlx->menu_map->size;
			if (mlx->map->blocks[i][j] == WALL)
				draw_square(mlx, (int [2]){x, y}, mlx->menu_map->size, 0xFFFFFF0F);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, mlx->menu_map->x, mlx->menu_map->y);
}
