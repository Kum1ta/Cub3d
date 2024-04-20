/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_part.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 00:10:39 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/19 00:12:34 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./main_menu.h"

void	graphics_part_settings(t_mlx *mlx, int diff)
{
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 36);
	mlx_string_put(mlx->mlx, mlx->win, 70, 285 + diff, 0xFFFFFFFF,
		"Graphics");
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 24);
	mlx_string_put(mlx->mlx, mlx->win, 90, 330 + diff, 0xFFFFFFFF,
		"Resolution");
	list_button_resolution(mlx, (int [2]){90, 350 + diff});
	mlx_string_put(mlx->mlx, mlx->win, 90, 440 + diff, 0xFFFFFFFF,
		"Quality");
	list_button_quality(mlx, (int [2]){90, 460 + diff});
	mlx_string_put(mlx->mlx, mlx->win, 90, 520 + diff, 0xFFFFFFFF,
		"Anti aliasing (SS)");
	list_button_aa(mlx, (int [2]){90, 540 + diff});
}

void	basics_part_settings(t_mlx *mlx, int diff)
{
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 36);
	mlx_string_put(mlx->mlx, mlx->win, 70, 155 + diff, 0xFFFFFFFF, "Basics");
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 24);
	mlx_string_put(mlx->mlx, mlx->win, 80, 200 + diff,
		0xFFFFFFFF, "Show fps :");
	list_button_fps(mlx, (int [2]){270, 185 + diff});
	mlx_string_put(mlx->mlx, mlx->win, 80, 235 + diff, 0xFFFFFFFF,
		"Texture  :");
	list_button_texture(mlx, (int [2]){270, 220 + diff});
}

void	minimap_part_settings(t_mlx *mlx, int diff)
{
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 36);
	mlx_string_put(mlx->mlx, mlx->win, 70, 630 + diff, 0xFFFFFFFF, "Mini map");
	mlx_set_font_scale(mlx->mlx, mlx->win, "fonts/rubik.ttf", 24);
	mlx_string_put(mlx->mlx, mlx->win, 90, 680 + diff,
		0xFFFFFFFF, "Show       :");
	list_button_mini_map(mlx, (int [2]){300, 665 + diff});
	mlx_string_put(mlx->mlx, mlx->win, 90, 710 + diff,
		0xFFFFFFFF, "Position");
	list_position_mini_map(mlx, (int [2]){93, 725 + diff});
}
