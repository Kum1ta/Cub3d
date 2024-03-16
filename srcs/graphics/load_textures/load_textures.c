/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:31:15 by edbernar          #+#    #+#             */
/*   Updated: 2024/03/16 20:45:34 by edbernar         ###   ########.fr       */
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

	return (0);
}
