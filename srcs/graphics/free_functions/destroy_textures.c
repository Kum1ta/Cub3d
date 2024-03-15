/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:07:07 by edbernar          #+#    #+#             */
/*   Updated: 2024/03/15 15:58:31 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../graphics.h"

int	destroy_textures(t_mlx *mlx)
{
	if (!mlx || !mlx->textures)
		return (0);

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

	if (mlx->textures->floor && mlx->textures->floor->img)
		mlx_destroy_image(mlx->mlx, mlx->textures->floor->img);
	free(mlx->textures->floor);

	if (mlx->textures->ceiling && mlx->textures->ceiling->img)
		mlx_destroy_image(mlx->mlx, mlx->textures->ceiling->img);
	free(mlx->textures->ceiling);

	if (mlx->textures->player_icon_larg_map && mlx->textures->player_icon_larg_map->img)
		mlx_destroy_image(mlx->mlx, mlx->textures->player_icon_larg_map->img);
	free(mlx->textures->player_icon_larg_map);

	free(mlx->textures);
	return (0);
}
