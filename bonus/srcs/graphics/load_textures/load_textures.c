/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:31:15 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/10 14:02:57 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../graphics.h"

void	init_textures(t_loadeds_textures *textures)
{
	textures->north = NULL;
	textures->south = NULL;
	textures->east = NULL;
	textures->west = NULL;
	textures->floor = NULL;
	textures->ceiling = NULL;
	textures->player_ico = NULL;
	textures->fist_inv = NULL;
	textures->knife_inv = NULL;
	textures->weapon_inv = NULL;
	textures->weapon_game = NULL;
	textures->fist_game = NULL;
	textures->knife_game = NULL;
	textures->fire_gun = NULL;
}

int	load_textures(t_mlx *mlx)
{
	mlx->textures = malloc(sizeof(t_loadeds_textures));
	if (!mlx->textures)
		return (error_int("Cube3d: Error load_texture()\n", 1));
	init_textures(mlx->textures);

	mlx->textures->north = malloc(sizeof(t_img));
	if (!mlx->textures->north)
		return ((int [2]){destroy_textures(mlx), error_int("Cube3d: Error load_texture()\n", 1)}[1]);
	mlx->textures->north->img = mlx_png_file_to_image(mlx->mlx, "textures/map/wall_north.png", &mlx->textures->north->width, &mlx->textures->north->height);
	if (!mlx->textures->north->img)
		return ((int [2]){destroy_textures(mlx), error_int("Cube3d: Error load_texture()\n", 1)}[1]);

	mlx->textures->south = malloc(sizeof(t_img));
	if (!mlx->textures->south)
		return ((int [2]){destroy_textures(mlx), error_int("Cube3d: Error load_texture()\n", 1)}[1]);
	mlx->textures->south->img = mlx_png_file_to_image(mlx->mlx, "textures/map/wall_south.png", &mlx->textures->south->width, &mlx->textures->south->height);
	if (!mlx->textures->south->img)
		return ((int [2]){destroy_textures(mlx), error_int("Cube3d: Error load_texture()\n", 1)}[1]);
	
	mlx->textures->east = malloc(sizeof(t_img));
	if (!mlx->textures->east)
		return ((int [2]){destroy_textures(mlx), error_int("Cube3d: Error load_texture()\n", 1)}[1]);
	mlx->textures->east->img = mlx_png_file_to_image(mlx->mlx, "textures/map/wall_east.png", &mlx->textures->east->width, &mlx->textures->east->height);
	if (!mlx->textures->east->img)
		return ((int [2]){destroy_textures(mlx), error_int("Cube3d: Error load_texture()\n", 1)}[1]);

	mlx->textures->west = malloc(sizeof(t_img));
	if (!mlx->textures->west)
		return ((int [2]){destroy_textures(mlx), error_int("Cube3d: Error load_texture()\n", 1)}[1]);
	mlx->textures->west->img = mlx_png_file_to_image(mlx->mlx, "textures/map/wall_west.png", &mlx->textures->west->width, &mlx->textures->west->height);
	if (!mlx->textures->west->img)
		return ((int [2]){destroy_textures(mlx), error_int("Cube3d: Error load_texture()\n", 1)}[1]);

	mlx->textures->floor = malloc(sizeof(t_img));
	if (!mlx->textures->floor)
		return ((int [2]){destroy_textures(mlx), error_int("Cube3d: Error load_texture()\n", 1)}[1]);
	mlx->textures->floor->img = mlx_png_file_to_image(mlx->mlx, "textures/map/floor.png", &mlx->textures->floor->width, &mlx->textures->floor->height);
	if (!mlx->textures->floor->img)
		return ((int [2]){destroy_textures(mlx), error_int("Cube3d: Error load_texture()\n", 1)}[1]);

	mlx->textures->player_ico = malloc(sizeof(t_img));
	if (!mlx->textures->player_ico)
		return ((int [2]){destroy_textures(mlx), error_int("Cube3d: Error load_texture()\n", 1)}[1]);
	mlx->textures->player_ico->img = mlx_png_file_to_image(mlx->mlx, "textures/mini_map/player.png", &mlx->textures->player_ico->width, &mlx->textures->player_ico->height);
	if (!mlx->textures->player_ico->img)
		return ((int [2]){destroy_textures(mlx), error_int("Cube3d: Error load_texture()\n", 1)}[1]);

	mlx->textures->fist_inv = malloc(sizeof(t_img));
	if (!mlx->textures->fist_inv)
		return ((int [2]){destroy_textures(mlx), error_int("Cube3d: Error load_texture()\n", 1)}[1]);
	mlx->textures->fist_inv->img = mlx_png_file_to_image(mlx->mlx, "textures/inventory/fist.png", &mlx->textures->fist_inv->width, &mlx->textures->fist_inv->height);
	if (!mlx->textures->fist_inv->img)
		return ((int [2]){destroy_textures(mlx), error_int("Cube3d: Error load_texture()\n", 1)}[1]);
	
	mlx->textures->knife_inv = malloc(sizeof(t_img));
	if (!mlx->textures->knife_inv)
		return ((int [2]){destroy_textures(mlx), error_int("Cube3d: Error load_texture()\n", 1)}[1]);
	mlx->textures->knife_inv->img = mlx_png_file_to_image(mlx->mlx, "textures/inventory/knife.png", &mlx->textures->knife_inv->width, &mlx->textures->knife_inv->height);
	if (!mlx->textures->knife_inv->img)
		return ((int [2]){destroy_textures(mlx), error_int("Cube3d: Error load_texture()\n", 1)}[1]);
	
	mlx->textures->weapon_inv = malloc(sizeof(t_img));
	if (!mlx->textures->weapon_inv)
		return ((int [2]){destroy_textures(mlx), error_int("Cube3d: Error load_texture()\n", 1)}[1]);
	mlx->textures->weapon_inv->img = mlx_png_file_to_image(mlx->mlx, "textures/inventory/weapon.png", &mlx->textures->weapon_inv->width, &mlx->textures->weapon_inv->height);
	if (!mlx->textures->weapon_inv->img)
		return ((int [2]){destroy_textures(mlx), error_int("Cube3d: Error load_texture()\n", 1)}[1]);

	mlx->textures->weapon_game = malloc(sizeof(t_img));
	if (!mlx->textures->weapon_game)
		return ((int [2]){destroy_textures(mlx), error_int("Cube3d: Error load_texture()\n", 1)}[1]);
	mlx->textures->weapon_game->img = mlx_png_file_to_image(mlx->mlx, "textures/game/weapon.png", &mlx->textures->weapon_game->width, &mlx->textures->weapon_game->height);
	if (!mlx->textures->weapon_game->img)
		return ((int [2]){destroy_textures(mlx), error_int("Cube3d: Error load_texture()\n", 1)}[1]);
	
	// mlx->textures->fist_game = malloc(sizeof(t_img));
	// if (!mlx->textures->fist_game)
	// 	return ((int [2]){destroy_textures(mlx), error_int("Cube3d: Error load_texture()\n", 1)}[1]);
	// mlx->textures->fist_game->img = mlx_png_file_to_image(mlx->mlx, "textures/game/fist.png", &mlx->textures->fist_game->width, &mlx->textures->fist_game->height);
	// if (!mlx->textures->fist_game->img)
	// 	return ((int [2]){destroy_textures(mlx), error_int("Cube3d: Error load_texture()\n", 1)}[1]);

	// mlx->textures->knife_game = malloc(sizeof(t_img));
	// if (!mlx->textures->knife_game)
	// 	return ((int [2]){destroy_textures(mlx), error_int("Cube3d: Error load_texture()\n", 1)}[1]);
	// mlx->textures->knife_game->img = mlx_png_file_to_image(mlx->mlx, "textures/game/knife.png", &mlx->textures->knife_game->width, &mlx->textures->knife_game->height);
	// if (!mlx->textures->knife_game->img)
	// 	return ((int [2]){destroy_textures(mlx), error_int("Cube3d: Error load_texture()\n", 1)}[1]);

	mlx->textures->fire_gun = malloc(sizeof(t_img));
	if (!mlx->textures->fire_gun)
		return ((int [2]){destroy_textures(mlx), error_int("Cube3d: Error load_texture()\n", 1)}[1]);
	mlx->textures->fire_gun->img = mlx_png_file_to_image(mlx->mlx, "textures/game/fire.png", &mlx->textures->fire_gun->width, &mlx->textures->fire_gun->height);
	if (!mlx->textures->fire_gun->img)
		return ((int [2]){destroy_textures(mlx), error_int("Cube3d: Error load_texture()\n", 1)}[1]);
	
	return (0);
}
