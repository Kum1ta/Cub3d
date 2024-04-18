/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:24:58 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/18 15:25:48 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "larg_map.h"


void	init_antialiasing(t_mlx *mlx, t_selected (*selected)[22])
{
	if (mlx->stg->antialiasing == 1)
		(*selected)[11] = SELECTED;
	else if (mlx->stg->antialiasing == 2)
		(*selected)[12] = SELECTED;
	else if (mlx->stg->antialiasing == 4)
		(*selected)[13] = SELECTED;
	else if (mlx->stg->antialiasing == 8)
		(*selected)[14] = SELECTED;
}

void	init_button_lm(t_mlx *mlx, t_selected (*selected)[22], int *init)
{
	int	i;

	i = -1;
	*init = 1;
	if (mlx->stg->show_fps)
		(*selected)[1] = SELECTED;
	else
		(*selected)[0] = SELECTED;
	if (mlx->stg->quality == 5)
		(*selected)[7] = SELECTED;
	else if (mlx->stg->quality == 3)
		(*selected)[8] = SELECTED;
	else if (mlx->stg->quality == 2)
		(*selected)[9] = SELECTED;
	else if (mlx->stg->quality == 1)
		(*selected)[10] = SELECTED;
	if (mlx->stg->texture)
		(*selected)[16] = SELECTED;
	else
		(*selected)[15] = SELECTED;
	init_antialiasing(mlx, selected);
	mlx->stg_win.sensibility_x = mlx->stg->sensibility_x;
	mlx->stg_win.sensibility_y = mlx->stg->sensibility_y;
}