/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supersampling_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:44:52 by psalame           #+#    #+#             */
/*   Updated: 2024/04/27 15:11:58 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raycasting.h"

static inline int	min(int a, int b)
{
	if (a > b)
		return (b);
	else
		return (a);
}

static inline int	choose_anti_aliasing(t_mlx *mlx, int distance)
{
	int	lvl;

	if (mlx->stg->antialiasing == 2)
	{
		if (distance < 2)
			lvl = 1;
		else
			lvl = 2;
	}
	else if (distance < 2)
		lvl = 1;
	else if (distance < 5)
		lvl = mlx->stg->antialiasing / 4;
	else if (distance < 10)
		lvl = mlx->stg->antialiasing / 2;
	else
		lvl = mlx->stg->antialiasing;
	return (lvl);
}

static inline void	calc_ss_color(t_mlx *mlx, int pos[2],
						int shift_pos[2], int color[3])
{
	int	color_tmp;

	color_tmp = mlx_get_image_pixel(mlx->mlx, ((t_img *)mlx->tmp)->img,
			min(pos[0] + shift_pos[0], ((t_img *)mlx->tmp)->width - 1),
			min(pos[1] + shift_pos[1], ((t_img *)mlx->tmp)->height - 1));
	color[0] += (color_tmp & 0x00FF0000) >> 16;
	color[2] += (color_tmp & 0x0000FF00) >> 8;
	color[1] += color_tmp & 0x000000FF;
}

int	get_ss_color(t_mlx *mlx, int x, int y, int distance)
{
	int		color[3];
	int		shift_pos[2];
	int		lvl;

	if (mlx->stg->texture)
		return (0xFFAA0011);
	if (mlx->stg->antialiasing == 1)
		return (mlx_get_image_pixel(mlx->mlx, ((t_img *)mlx->tmp)->img, x, y));
	lvl = choose_anti_aliasing(mlx, distance);
	ft_bzero(color, 3 * sizeof(int));
	shift_pos[1] = -1;
	while (++shift_pos[1] < lvl)
	{
		shift_pos[0] = -1;
		while (++shift_pos[0] < lvl)
			calc_ss_color(mlx, (int [2]){x, y}, shift_pos, color);
	}
	return (255 << 24 | (color[0] / (lvl * lvl)) << 16
		| (color[2] / (lvl * lvl)) << 8 | (color[1] / (lvl * lvl)));
}
