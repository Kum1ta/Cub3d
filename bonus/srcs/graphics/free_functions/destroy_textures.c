/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:07:07 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/10 22:00:59 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../graphics.h"

static void	wall_texture_destroy(t_mlx *mlx)
{
	if (mlx->textures->north && mlx->textures->north->img)
		mlx_destroy_image(mlx->mlx, mlx->textures->north->img);
	free(mlx->textures->north);
	if (mlx->textures->south && mlx->textures->south->img)
		mlx_destroy_image(mlx->mlx, mlx->textures->south->img);
	free(mlx->textures->south);
	if (mlx->textures->east && mlx->textures->east->img)
		mlx_destroy_image(mlx->mlx, mlx->textures->east->img);
	free(mlx->textures->east);
	if (mlx->textures->west && mlx->textures->west->img)
		mlx_destroy_image(mlx->mlx, mlx->textures->west->img);
	free(mlx->textures->west);
}

int	destroy_textures(t_mlx *mlx)
{
	if (!mlx || !mlx->textures)
		return (0);
	wall_texture_destroy(mlx);
	if (mlx->textures->floor && mlx->textures->floor->img)
		mlx_destroy_image(mlx->mlx, mlx->textures->floor->img);
	free(mlx->textures->floor);
	if (mlx->textures->ceiling && mlx->textures->ceiling->img)
		mlx_destroy_image(mlx->mlx, mlx->textures->ceiling->img);
	free(mlx->textures->ceiling);
	if (mlx->textures->player_ico && mlx->textures->player_ico->img)
		mlx_destroy_image(mlx->mlx, mlx->textures->player_ico->img);
	free(mlx->textures->player_ico);
	if (mlx->textures->fist_inv && mlx->textures->fist_inv->img)
		mlx_destroy_image(mlx->mlx, mlx->textures->fist_inv->img);
	free(mlx->textures->fist_inv);
	if (mlx->textures->knife_inv && mlx->textures->knife_inv->img)
		mlx_destroy_image(mlx->mlx, mlx->textures->knife_inv->img);
	free(mlx->textures->knife_inv);
	if (mlx->textures->weapon_inv && mlx->textures->weapon_inv->img)
		mlx_destroy_image(mlx->mlx, mlx->textures->weapon_inv->img);
	free(mlx->textures->weapon_inv);
	if (mlx->textures->weapon_game && mlx->textures->weapon_game->img)
		mlx_destroy_image(mlx->mlx, mlx->textures->weapon_game->img);
	free(mlx->textures->weapon_game);
	if (mlx->textures->fist_game && mlx->textures->fist_game->img)
		mlx_destroy_image(mlx->mlx, mlx->textures->fist_game->img);
	free(mlx->textures->fist_game);
	if (mlx->textures->knife_game && mlx->textures->knife_game->img)
		mlx_destroy_image(mlx->mlx, mlx->textures->knife_game->img);
	free(mlx->textures->knife_game);
	if (mlx->textures->fire_gun && mlx->textures->fire_gun->img)
		mlx_destroy_image(mlx->mlx, mlx->textures->fire_gun->img);
	free(mlx->textures->fire_gun);
	if (mlx->textures->player.img)
		mlx_destroy_image(mlx->mlx, mlx->textures->player.img);
	free(mlx->textures);
	return (0);
}
