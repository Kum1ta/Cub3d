/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:07:07 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/02 20:03:15 by edbernar         ###   ########.fr       */
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
	if (!mlx)
		return (0);
	wall_texture_destroy(mlx);
	free(mlx->textures);
	return (0);
}
