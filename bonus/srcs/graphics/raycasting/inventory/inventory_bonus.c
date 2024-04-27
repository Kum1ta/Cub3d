/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:49:38 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/27 15:12:00 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raycasting.h"

static inline void	init_circle_img(t_mlx *mlx, int radius, t_img *img)
{
	int	i;
	int	j;
	int	dist;

	i = 0;
	while (img->img && i <= 2 * radius)
	{
		j = 0;
		while (j <= 2 * radius)
		{
			dist = (radius - i) * (radius - i) + (radius - j) * (radius - j);
			if (dist <= radius * radius)
				mlx_set_image_pixel(mlx->mlx, img->img, j + 2, i + 2,
					0xFF343434);
			else if (dist <= (radius + 2) * (radius + 2))
				mlx_set_image_pixel(mlx->mlx, img->img, j + 2, i + 2,
					0xFF91a3b0);
			j++;
		}
		i++;
	}
}

static void	draw_circle(t_mlx *mlx, int pos[2], int radius, int need_free)
{
	static t_img	img;

	if (need_free)
	{
		if (img.img)
			mlx_destroy_image(mlx->mlx, img.img);
		img.img = NULL;
		return ;
	}
	if (!img.img)
	{
		img.width = 2 * radius + 10;
		img.height = 2 * radius + 10;
		img.img = mlx_new_image(mlx->mlx, img.width, img.height);
		init_circle_img(mlx, radius, &img);
	}
	if (img.img)
		draw_image_to_window(mlx, &img, pos, (int [2]){img.width, img.height});
}

void	inventory(t_mlx *mlx, int need_free)
{
	(void)mlx;
	draw_circle(mlx, (int [2]){mlx->stg->width - 200, mlx->stg->height - 200},
		75, need_free);
	if (need_free)
		return ;
	if (mlx->player->actual_weapon == WEAPON_INV)
		draw_image_to_window(mlx, &mlx->textures->weapon_inv,
			(int [2]){mlx->stg->width - 170, mlx->stg->height - 170},
			(int [2]){mlx->textures->weapon_inv.width,
			mlx->textures->weapon_inv.height});
	else if (mlx->player->actual_weapon == KNIFE_INV)
		draw_image_to_window(mlx, &mlx->textures->knife_inv,
			(int [2]){mlx->stg->width - 170, mlx->stg->height - 170},
			(int [2]){mlx->textures->knife_inv.width,
			mlx->textures->knife_inv.height});
	else if (mlx->player->actual_weapon == FIST_INV)
		draw_image_to_window(mlx, &mlx->textures->fist_inv,
			(int [2]){mlx->stg->width - 170, mlx->stg->height - 170},
			(int [2]){mlx->textures->fist_inv.width,
			mlx->textures->fist_inv.height});
}
