/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_list_button_two_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 00:06:05 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/27 14:52:39 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./main_menu.h"

void	not_selected_button(t_mlx *mlx, t_selected selected[22],
		int xy[2], int list[3])
{
	window_pixel_put(mlx, xy[0], xy[1], 0x5F101010);
	if (mlx->mouse->pressed_left)
	{
		while (list[0] <= list[1])
			selected[list[0]++] = NOT_SELECTED;
		selected[list[2]] = SELECTED;
		mlx->mouse->pressed_left = 0;
	}
}

int	add_case(t_mlx *mlx, int pos[4], char *str, int list[3])
{
	static t_selected	selected[22];
	static int			init = 0;
	int					xy[2];

	xy[0] = pos[0] - 1;
	if (!init)
		init_button(mlx, selected, &init);
	while (++xy[0] < pos[2])
	{
		xy[1] = pos[1] - 1;
		while (++xy[1] < pos[3])
		{
			if (xy[0] == pos[0] || xy[0] == pos[2] - 1
				|| xy[1] == pos[1] || xy[1] == pos[3] - 1)
				window_pixel_put(mlx, xy[0], xy[1], 0xFFFFFFFF);
			else if (mlx->mouse->x > pos[0] && mlx->mouse->x < pos[2]
				&& mlx->mouse->y > pos[1] && mlx->mouse->y < pos[3]
				&& selected[list[2]] == NOT_SELECTED)
				not_selected_button(mlx, selected, xy, list);
			else if (selected[list[2]] == SELECTED)
				window_pixel_put(mlx, xy[0], xy[1], 0x5F0FF000);
		}
	}
	mlx_string_put(mlx->mlx, mlx->win, pos[0] + 30, pos[1] + 17, WHITE, str);
	return (selected[list[2]] == SELECTED);
}

void	list_button_fps(t_mlx *mlx, int xy[2])
{
	if (add_case(mlx, (int [4]){xy[0], xy[1], xy[0] + 20, xy[1] + 20},
		"Off", (int [3]){0, 1, 0}))
		mlx->stg_win.show_fps = 0;
	if (add_case(mlx, (int [4]){xy[0] + 100, xy[1], xy[0] + 120, xy[1] + 20},
		"On", (int [3]){0, 1, 1}))
		mlx->stg_win.show_fps = 1;
}

void	list_bigger_resolution(t_mlx *mlx, int xy[2])
{
	if (add_case(mlx, (int [4]){xy[0] + 530, xy[1], xy[0] + 550, xy[1] + 20},
		"1600x900", (int [3]){2, 6, 5}))
	{
		mlx->stg_win.width = 1600;
		mlx->stg_win.height = 900;
	}
	if (add_case(mlx, (int [4]){xy[0], xy[1] + 30, xy[0] + 20, xy[1] + 50},
		"1920x1080", (int [3]){2, 6, 6}))
	{
		mlx->stg_win.width = 1920;
		mlx->stg_win.height = 1080;
	}
}

void	list_button_resolution(t_mlx *mlx, int xy[2])
{
	if (add_case(mlx, (int [4]){xy[0], xy[1], xy[0] + 20, xy[1] + 20},
		"800x600", (int [3]){2, 6, 2}))
	{
		mlx->stg_win.width = 800;
		mlx->stg_win.height = 600;
	}
	if (add_case(mlx, (int [4]){xy[0] + 170, xy[1], xy[0] + 190, xy[1] + 20},
		"1024x768", (int [3]){2, 6, 3}))
	{
		mlx->stg_win.width = 1024;
		mlx->stg_win.height = 768;
	}
	if (add_case(mlx, (int [4]){xy[0] + 350, xy[1], xy[0] + 370, xy[1] + 20},
		"1280x800", (int [3]){2, 6, 4}))
	{
		mlx->stg_win.width = 1280;
		mlx->stg_win.height = 800;
	}
	list_bigger_resolution(mlx, xy);
}
