/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:07:07 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/15 14:00:14 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../graphics.h"

static void	wall_texture_destroy(t_mlx *mlx)
{
	if (mlx->textures->north.img)
		mlx_destroy_image(mlx->mlx, mlx->textures->north.img);
	if (mlx->textures->south.img)
		mlx_destroy_image(mlx->mlx, mlx->textures->south.img);
	if (mlx->textures->east.img)
		mlx_destroy_image(mlx->mlx, mlx->textures->east.img);
	if (mlx->textures->west.img)
		mlx_destroy_image(mlx->mlx, mlx->textures->west.img);
}

int	destroy_textures(t_mlx *mlx)
{
	if (!mlx || !mlx->textures)
		return (0);
	wall_texture_destroy(mlx);
	if (mlx->textures->fist_inv.img)
		mlx_destroy_image(mlx->mlx, mlx->textures->fist_inv.img);
	if (mlx->textures->knife_inv.img)
		mlx_destroy_image(mlx->mlx, mlx->textures->knife_inv.img);
	if (mlx->textures->weapon_inv.img)
		mlx_destroy_image(mlx->mlx, mlx->textures->weapon_inv.img);
	if (mlx->textures->weapon_game.img)
		mlx_destroy_image(mlx->mlx, mlx->textures->weapon_game.img);
	if (mlx->textures->knife_game.img)
		mlx_destroy_image(mlx->mlx, mlx->textures->knife_game.img);
	if (mlx->textures->fire_gun.img)
		mlx_destroy_image(mlx->mlx, mlx->textures->fire_gun.img);
	if (mlx->textures->player[0].img)
		mlx_destroy_image(mlx->mlx, mlx->textures->player[0].img);
	if (mlx->textures->player[1].img)
		mlx_destroy_image(mlx->mlx, mlx->textures->player[1].img);
	if (mlx->textures->player[2].img)
		mlx_destroy_image(mlx->mlx, mlx->textures->player[2].img);
	if (mlx->textures->player[3].img)
		mlx_destroy_image(mlx->mlx, mlx->textures->player[3].img);
	free(mlx->textures);
	return (0);
}
