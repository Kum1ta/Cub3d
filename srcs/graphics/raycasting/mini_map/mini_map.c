/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 18:27:58 by edbernar          #+#    #+#             */
/*   Updated: 2024/03/17 19:21:53 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raycasting.h"

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
		mlx_put_image_to_window(mlx->mlx, mlx->win, img, 50, HEIGHT - 225);
		return ;
	}
	while (y < 200)
	{
		x = 0;
		mlx_set_image_pixel(mlx->mlx, img, x++, y, 0xF091a3b0);
		while (x < 350)
		{
			if (y == 199 || y == 0)
				mlx_set_image_pixel(mlx->mlx, img, x, y, 0xF091a3b0);
			else
				mlx_set_image_pixel(mlx->mlx, img, x, y, 0xF0343434);
			x++;
		}
		mlx_set_image_pixel(mlx->mlx, img, x, y, 0xF091a3b0);
		y++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, img, 50, HEIGHT - 225);
}
