/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_textures_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:07:07 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/27 15:11:36 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../graphics.h"

static inline void	_destroy_textures(t_mlx *mlx)
{
	const t_img	*imgs[] = {&mlx->textures->door,
		&mlx->textures->weapon_inv, &mlx->textures->knife_inv,
		&mlx->textures->fist_inv, &mlx->textures->weapon_game,
		&mlx->textures->knife_game, &mlx->textures->fire_gun,
		&mlx->textures->player[0], &mlx->textures->player[1],
		&mlx->textures->player[2], &mlx->textures->player[3],
		&mlx->textures->health_kit, &mlx->textures->north,
		&mlx->textures->south, &mlx->textures->east, &mlx->textures->west,
		NULL};
	int			i;

	i = -1;
	while (imgs[++i])
		if (imgs[i]->img)
			mlx_destroy_image(mlx->mlx, imgs[i]->img);
}

int	destroy_textures(t_mlx *mlx)
{
	if (!mlx || !mlx->textures)
		return (0);
	_destroy_textures(mlx);
	free(mlx->textures);
	return (0);
}
