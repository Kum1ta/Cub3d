/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_list_button_one_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 00:02:31 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/27 15:11:48 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./main_menu.h"

void	list_button_quality(t_mlx *mlx, int xy[2])
{
	if (add_case(mlx, (int [4]){xy[0], xy[1], xy[0] + 20, xy[1] + 20},
		"Very low", (int [3]){7, 10, 7}))
		mlx->stg_win.quality = 5;
	if (add_case(mlx, (int [4]){xy[0] + 180, xy[1], xy[0] + 200, xy[1] + 20},
		"Low", (int [3]){7, 10, 8}))
		mlx->stg_win.quality = 3;
	if (add_case(mlx, (int [4]){xy[0] + 275, xy[1], xy[0] + 295, xy[1] + 20},
		"Medium", (int [3]){7, 10, 9}))
		mlx->stg_win.quality = 2;
	if (add_case(mlx, (int [4]){xy[0] + 425, xy[1], xy[0] + 445, xy[1] + 20},
		"High", (int [3]){7, 10, 10}))
		mlx->stg_win.quality = 1;
}

void	list_button_aa(t_mlx *mlx, int xy[2])
{
	if (add_case(mlx, (int [4]){xy[0], xy[1], xy[0] + 20, xy[1] + 20},
		"x1", (int [3]){11, 14, 11}))
		mlx->stg_win.anti_aliasing = 1;
	if (add_case(mlx, (int [4]){xy[0] + 100, xy[1], xy[0] + 120, xy[1] + 20},
		"x2", (int [3]){11, 14, 12}))
		mlx->stg_win.anti_aliasing = 2;
	if (add_case(mlx, (int [4]){xy[0] + 200, xy[1], xy[0] + 220, xy[1] + 20},
		"x4", (int [3]){11, 14, 13}))
		mlx->stg_win.anti_aliasing = 4;
	if (add_case(mlx, (int [4]){xy[0] + 300, xy[1], xy[0] + 320, xy[1] + 20},
		"x8", (int [3]){11, 14, 14}))
		mlx->stg_win.anti_aliasing = 8;
}

void	list_button_mini_map(t_mlx *mlx, int xy[2])
{
	if (add_case(mlx, (int [4]){xy[0], xy[1], xy[0] + 20, xy[1] + 20},
		"Off", (int [3]){15, 16, 15}))
		mlx->stg_win.show_mini_map = 0;
	if (add_case(mlx, (int [4]){xy[0] + 100, xy[1], xy[0] + 120, xy[1] + 20},
		"On", (int [3]){15, 16, 16}))
		mlx->stg_win.show_mini_map = 1;
}

void	list_position_mini_map(t_mlx *mlx, int xy[2])
{
	if (add_case(mlx, (int [4]){xy[0], xy[1], xy[0] + 20, xy[1] + 20},
		"top-left", (int [3]){17, 19, 17}))
		mlx->stg_win.pos_mini_map = 0;
	if (add_case(mlx, (int [4]){xy[0] + 200, xy[1], xy[0] + 220, xy[1] + 20},
		"top-right", (int [3]){17, 19, 18}))
		mlx->stg_win.pos_mini_map = 1;
	if (add_case(mlx, (int [4]){xy[0] + 400, xy[1], xy[0] + 420, xy[1] + 20},
		"bottom-left", (int [3]){17, 19, 19}))
		mlx->stg_win.pos_mini_map = 2;
}

void	list_button_texture(t_mlx *mlx, int xy[2])
{
	if (add_case(mlx, (int [4]){xy[0], xy[1], xy[0] + 20, xy[1] + 20},
		"Off", (int [3]){20, 21, 20}))
		mlx->stg_win.texture = 1;
	if (add_case(mlx, (int [4]){xy[0] + 100, xy[1], xy[0] + 120, xy[1] + 20},
		"On", (int [3]){20, 21, 21}))
		mlx->stg_win.texture = 0;
}
