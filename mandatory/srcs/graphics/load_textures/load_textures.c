/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:31:15 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/02 21:11:09 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../graphics.h"

int	load_textures(t_mlx *mlx)
{
	mlx->textures = ft_calloc(1, sizeof(t_loadeds_textures));
	if (!mlx->textures)
		return (error_int(ERROR_TXTE, 1));
	mlx->textures->north.img = mlx_png_file_to_image(mlx->mlx,
			mlx->map->texture.north, &mlx->textures->north.width,
			&mlx->textures->north.height);
	if (!mlx->textures->north.img)
		return ((int [2]){destroy_textures(mlx), error_int(ERROR_TXTE, 1)}[1]);
	mlx->textures->south.img = mlx_png_file_to_image(mlx->mlx,
			mlx->map->texture.south, &mlx->textures->south.width,
			&mlx->textures->south.height);
	if (!mlx->textures->south.img)
		return ((int [2]){destroy_textures(mlx), error_int(ERROR_TXTE, 1)}[1]);
	mlx->textures->east.img = mlx_png_file_to_image(mlx->mlx,
			mlx->map->texture.east, &mlx->textures->east.width,
			&mlx->textures->east.height);
	if (!mlx->textures->east.img)
		return ((int [2]){destroy_textures(mlx), error_int(ERROR_TXTE, 1)}[1]);
	mlx->textures->west.img = mlx_png_file_to_image(mlx->mlx,
			mlx->map->texture.west, &mlx->textures->west.width,
			&mlx->textures->west.height);
	if (!mlx->textures->west.img)
		return ((int [2]){destroy_textures(mlx), error_int(ERROR_TXTE, 1)}[1]);
	return (0);
}
