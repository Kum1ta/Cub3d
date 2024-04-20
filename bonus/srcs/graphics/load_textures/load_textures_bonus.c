/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:31:15 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/18 23:56:30 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../graphics.h"

static bool	load_texture(void *mlx, const char *path, t_img *img)
{
	img->img = mlx_png_file_to_image(mlx, (char *) path,
			&img->width, &img->height);
	return (img->img != NULL);
}

static inline bool	load_wall_textures(t_mlx *mlx)
{
	return (load_texture(mlx->mlx, mlx->map->texture.north,
			&mlx->textures->north)
		&& load_texture(mlx->mlx, mlx->map->texture.south,
			&mlx->textures->south)
		&& load_texture(mlx->mlx, mlx->map->texture.east,
			&mlx->textures->east)
		&& load_texture(mlx->mlx, mlx->map->texture.west,
			&mlx->textures->west));
}

static inline bool	load_game_textures(t_mlx *mlx)
{
	const char	*txts_path[] = {"textures/game/door.png",
		"textures/inventory/weapon.png",
		"textures/inventory/fist.png",
		"textures/inventory/knife.png",
		"textures/game/weapon.png",
		"textures/game/knife.png",
		"textures/game/fire.png",
		"textures/game/player_front.png",
		"textures/game/player_right.png",
		"textures/game/player_back.png",
		"textures/game/player_left.png",
		"textures/game/health_kit.png", NULL};
	t_img		*txt;
	int			i;

	txt = &mlx->textures->door;
	i = 0;
	while (txts_path[i])
		if (!load_texture(mlx->mlx, txts_path[i++], txt++))
			return (false);
	return (true);
}

int	load_textures(t_mlx *mlx)
{
	mlx->textures = ft_calloc(1, sizeof(t_loadeds_textures));
	if (!mlx->textures
		|| !load_wall_textures(mlx)
		|| !load_game_textures(mlx))
	{
		destroy_textures(mlx);
		return (error_int("Cube3d: Error load_texture()\n", 1));
	}
	return (0);
}
