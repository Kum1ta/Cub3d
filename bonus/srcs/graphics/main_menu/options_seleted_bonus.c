/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_seleted_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 00:08:39 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/27 15:11:49 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./main_menu.h"

void	init_antialiasing_settings(t_mlx *mlx, t_selected selected[22])
{
	if (mlx->stg->antialiasing == 1)
		selected[11] = SELECTED;
	else if (mlx->stg->antialiasing == 2)
		selected[12] = SELECTED;
	else if (mlx->stg->antialiasing == 4)
		selected[13] = SELECTED;
	else
		selected[14] = SELECTED;
}

void	init_minimap_settings(t_mlx *mlx, t_selected selected[22])
{
	if (mlx->stg->show_minimap)
		selected[16] = SELECTED;
	else
		selected[15] = SELECTED;
	if (mlx->stg->minimap_pos == 1)
		selected[18] = SELECTED;
	else if (mlx->stg->minimap_pos == 2)
		selected[19] = SELECTED;
	else
		selected[17] = SELECTED;
}

void	init_quality_settings(t_mlx *mlx, t_selected selected[22])
{
	if (mlx->stg->quality == 5)
		selected[7] = SELECTED;
	else if (mlx->stg->quality == 3)
		selected[8] = SELECTED;
	else if (mlx->stg->quality == 2)
		selected[9] = SELECTED;
	else
		selected[10] = SELECTED;
	if (mlx->stg->texture)
		selected[20] = SELECTED;
	else
		selected[21] = SELECTED;
}

void	init_button(t_mlx *mlx, t_selected selected[22], int *init)
{
	if (mlx->stg->show_fps)
		selected[1] = SELECTED;
	else
		selected[0] = SELECTED;
	if (mlx->stg->width == 1024 && mlx->stg->height == 768)
		selected[3] = SELECTED;
	else if (mlx->stg->width == 1280 && mlx->stg->height == 800)
		selected[4] = SELECTED;
	else if (mlx->stg->width == 1600 && mlx->stg->height == 900)
		selected[5] = SELECTED;
	else if (mlx->stg->width == 1920 && mlx->stg->height == 1080)
		selected[6] = SELECTED;
	else
		selected[2] = SELECTED;
	init_antialiasing_settings(mlx, selected);
	init_minimap_settings(mlx, selected);
	init_quality_settings(mlx, selected);
	mlx->stg_win.sensibility_x = mlx->stg->sensibility_x;
	mlx->stg_win.sensibility_y = mlx->stg->sensibility_y;
	*init = 1;
}
