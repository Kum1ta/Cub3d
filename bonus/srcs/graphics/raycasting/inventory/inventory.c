/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:49:38 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/15 19:29:30 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raycasting.h"

static void	draw_circle(t_mlx *mlx, int x, int y, int radius, int need_free)
{
	static void	*img = NULL;
	int			i;
	int			j;
	int			dist;

	i = 0;
	if (img)
		mlx_destroy_image(mlx->mlx, img);
	if (need_free)
		return ;
	img = mlx_new_image(mlx->mlx, 2 * radius + 10, 2 * radius + 10);
	while (i <= 2 * radius)
	{
		j = 0;
		while (j <= 2 * radius)
		{
			dist = (radius - i) * (radius - i) + (radius - j) * (radius - j);
			if (dist <= radius * radius)
				mlx_set_image_pixel(mlx->mlx, img, j + 2, i + 2, 0xF0343434);
			else if (dist <= (radius + 2) * (radius + 2))
				mlx_set_image_pixel(mlx->mlx, img, j + 2, i + 2, 0xF091a3b0);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, img, x, y);
}


void	inventory(t_mlx *mlx, int need_free)
{
	(void)mlx;
	draw_circle(mlx, mlx->stg->width - 200, mlx->stg->height - 200, 75, need_free);
	if (need_free)
		return ;
	if (mlx->player->actual_weapon == WEAPON_INV)
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->textures->weapon_inv.img, mlx->stg->width - 170, mlx->stg->height - 170);
	else if (mlx->player->actual_weapon == KNIFE_INV)
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->textures->knife_inv.img, mlx->stg->width - 170, mlx->stg->height - 170);
	else if (mlx->player->actual_weapon == FIST_INV)
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->textures->fist_inv.img, mlx->stg->width - 170, mlx->stg->height - 170);
}