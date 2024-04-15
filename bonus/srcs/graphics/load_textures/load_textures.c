/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:31:15 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/15 11:20:51 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../graphics.h"

static bool	load_texture(void *mlx, char *path, t_img *img)
{
	img->img = mlx_png_file_to_image(mlx, path, &img->width, &img->height);
	return (img->img != NULL);
}

int	load_textures(t_mlx *mlx)
{
	mlx->textures = ft_calloc(1, sizeof(t_loadeds_textures));
	if (!mlx->textures
		|| !load_texture(mlx->mlx, "textures/map/wall_north.png", &mlx->textures->north)
		|| !load_texture(mlx->mlx, "textures/map/wall_south.png", &mlx->textures->south)
		|| !load_texture(mlx->mlx, "textures/map/wall_east.png", &mlx->textures->east)
		|| !load_texture(mlx->mlx, "textures/map/wall_west.png", &mlx->textures->west)
		|| !load_texture(mlx->mlx, "textures/map/floor.png", &mlx->textures->floor)
		|| !load_texture(mlx->mlx, "textures/mini_map/player.png", &mlx->textures->player_ico)
		|| !load_texture(mlx->mlx, "textures/inventory/fist.png", &mlx->textures->fist_inv)
		|| !load_texture(mlx->mlx, "textures/inventory/knife.png", &mlx->textures->knife_inv)
		|| !load_texture(mlx->mlx, "textures/inventory/weapon.png", &mlx->textures->weapon_inv)
		|| !load_texture(mlx->mlx, "textures/game/weapon.png", &mlx->textures->weapon_game)
		|| !load_texture(mlx->mlx, "textures/game/fire.png", &mlx->textures->fire_gun)
		|| !load_texture(mlx->mlx, "textures/game/player_front.png", &mlx->textures->player[0])
		|| !load_texture(mlx->mlx, "textures/game/player_left.png", &mlx->textures->player[1])
		|| !load_texture(mlx->mlx, "textures/game/player_back.png", &mlx->textures->player[2])
		|| !load_texture(mlx->mlx, "textures/game/player_right.png", &mlx->textures->player[3]))
	{
		destroy_textures(mlx);
		return (error_int("Cube3d: Error load_texture()\n", 1));
	}
	return (0);
}
