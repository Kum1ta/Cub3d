/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_graphics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:58:28 by edbernar          #+#    #+#             */
/*   Updated: 2024/03/12 14:34:01 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./graphics.h"

// void	graphics_part(t_map *map)
void	graphics_part(t_block map[4][5])
{
	(void)map;
	t_mlx	*mlx;

	mlx = malloc(sizeof(t_mlx));
	if (!mlx)
		return ;
	mlx->mlx = mlx_init();
	// mlx->win = mlx_new_window(mlx->mlx, 1920, 1080, "Hello world !");
	// mlx_loop(mlx->mlx);
	free_all_graphics(mlx);
}