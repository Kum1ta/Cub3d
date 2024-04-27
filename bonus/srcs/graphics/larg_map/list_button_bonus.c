/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_button_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:22:23 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/27 15:19:23 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "larg_map.h"

void	list_button_quality_lm(t_mlx *mlx, int xy[2])
{
	if (add_case_lm(mlx, (int [4]){xy[0], xy[1], xy[0] + 20, xy[1] + 20},
		"Very low", (int [3]){7, 10, 7}))
		mlx->stg_win.quality = 5;
	if (add_case_lm(mlx, (int [4]){xy[0] + 180, xy[1], xy[0] + 200, xy[1] + 20},
		"Low", (int [3]){7, 10, 8}))
		mlx->stg_win.quality = 3;
	if (add_case_lm(mlx, (int [4]){xy[0] + 275, xy[1], xy[0] + 295, xy[1] + 20},
		"Medium", (int [3]){7, 10, 9}))
		mlx->stg_win.quality = 2;
	if (add_case_lm(mlx, (int [4]){xy[0] + 425, xy[1], xy[0] + 445, xy[1] + 20},
		"High", (int [3]){7, 10, 10}))
		mlx->stg_win.quality = 1;
}

void	list_button_aa_lm(t_mlx *mlx, int xy[2])
{
	if (add_case_lm(mlx, (int [4]){xy[0], xy[1], xy[0] + 20, xy[1] + 20}, "x1",
		(int [3]){11, 14, 11}))
		mlx->stg_win.anti_aliasing = 1;
	if (add_case_lm(mlx, (int [4]){xy[0] + 100, xy[1], xy[0] + 120, xy[1] + 20},
		"x2", (int [3]){11, 14, 12}))
		mlx->stg_win.anti_aliasing = 2;
	if (add_case_lm(mlx, (int [4]){xy[0] + 200, xy[1], xy[0] + 220, xy[1] + 20},
		"x4", (int [3]){11, 14, 13}))
		mlx->stg_win.anti_aliasing = 4;
	if (add_case_lm(mlx, (int [4]){xy[0] + 300, xy[1], xy[0] + 320, xy[1] + 20},
		"x8", (int [3]){11, 14, 14}))
		mlx->stg_win.anti_aliasing = 8;
}

void	list_button_texture_lm(t_mlx *mlx, int xy[2])
{
	if (add_case_lm(mlx, (int [4]){xy[0], xy[1], xy[0] + 20, xy[1] + 20},
		"Off", (int [3]){15, 16, 15}))
		mlx->stg_win.texture = 1;
	if (add_case_lm(mlx, (int [4]){xy[0] + 100, xy[1], xy[0] + 120, xy[1] + 20},
		"On", (int [3]){15, 16, 16}))
		mlx->stg_win.texture = 0;
}

int	add_case_lm(t_mlx *mlx, int pos[4], char *str, int list[3])
{
	static t_selected	selected[22];
	static int			init = 0;
	int					xy[2];

	xy[0] = pos[0] - 1;
	if (!init)
		init_button_lm(mlx, &selected, &init);
	while (++xy[0] < pos[2])
	{
		xy[1] = pos[1] - 1;
		while (++xy[1] < pos[3])
		{
			if ((xy[0] == pos[0] || xy[0] == pos[2] - 1
				|| xy[1] == pos[1] || xy[1] == pos[3] - 1))
				window_pixel_put(mlx, xy[0], xy[1], 0xFFFFFFFF);
			else if (mlx->mouse->x > pos[0] && mlx->mouse->x < pos[2]
				&& mlx->mouse->y > pos[1] && mlx->mouse->y < pos[3]
				&& selected[list[2]] == NOT_SELECTED)
				not_selected_button_lm(mlx, selected, xy, list);
			else if (selected[list[2]] == SELECTED)
				window_pixel_put(mlx, xy[0], xy[1], 0x5F0FF000);
		}
	}
	mlx_string_put(mlx->mlx, mlx->win, pos[0] + 30, pos[1] + 17, WHITE, str);
	return (selected[list[2]] == SELECTED);
}

void	list_button_fps_lm(t_mlx *mlx, int xy[2])
{
	if (add_case_lm(mlx, (int [4]){xy[0], xy[1],
			xy[0] + 20, xy[1] + 20}, "Off", (int [3]){0, 1, 0}))
		mlx->stg_win.show_fps = 0;
	if (add_case_lm(mlx, (int [4]){xy[0] + 100,
			xy[1], xy[0] + 120, xy[1] + 20}, "On", (int [3]){0, 1, 1}))
		mlx->stg_win.show_fps = 1;
}
