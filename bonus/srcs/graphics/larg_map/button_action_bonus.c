/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:26:33 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/18 17:16:59 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "larg_map.h"

void	not_selected_button_lm(t_mlx *mlx, t_selected selected[22],
		int xy[2], int list[3])
{
	mlx_pixel_put(mlx->mlx, mlx->win, xy[0], xy[1], 0x5F101010);
	if (mlx->mouse->pressed_left)
	{
		while (list[0] <= list[1])
			selected[list[0]++] = NOT_SELECTED;
		selected[list[2]] = SELECTED;
		mlx->mouse->pressed_left = 0;
	}
}

char	*button_main_lm(void *mlx, int action)
{
	if (action == 0)
		return ("Back");
	((t_mlx *)mlx)->mouse->pressed_left = 0;
	((t_mlx *)mlx)->actuel_menu = MAP_LARG_MENU;
	((t_mlx *)mlx)->stg_win.width = ((t_mlx *)mlx)->stg->width;
	((t_mlx *)mlx)->stg_win.height = ((t_mlx *)mlx)->stg->height;
	((t_mlx *)mlx)->stg_win.show_mini_map = ((t_mlx *)mlx)->stg->show_minimap;
	change_config_file_lm(&((t_mlx *)mlx)->stg_win);
	((t_mlx *)mlx)->stg->show_fps = ((t_mlx *)mlx)->stg_win.show_fps;
	((t_mlx *)mlx)->stg->antialiasing = ((t_mlx *)mlx)->stg_win.anti_aliasing;
	((t_mlx *)mlx)->stg->quality = ((t_mlx *)mlx)->stg_win.quality;
	((t_mlx *)mlx)->stg->texture = ((t_mlx *)mlx)->stg_win.texture;
	((t_mlx *)mlx)->stg->sensibility_x = ((t_mlx *)mlx)->stg_win.sensibility_x;
	((t_mlx *)mlx)->stg->sensibility_y = ((t_mlx *)mlx)->stg_win.sensibility_y;
	return (NULL);
}

char	*button_option_lm(void *mlx, int action)
{
	if (action == 0)
		return ("Options");
	((t_mlx *)mlx)->actuel_menu = OPTIONS_LM;
	return (NULL);
}

char	*main_menu_lm(void *mlxRaw, int action)
{
	t_mlx	*mlx;

	if (action == 0)
		return ("Quit");
	mlx = mlxRaw;
	mlx->actuel_menu = MAIN_MENU;
	if (mlx->game_server.status == CONNECTED)
		close_server(&mlx->game_server, DISCONNECTED);
	return (NULL);
}

char	*button_resume_lm(void *mlx_raw, int action)
{
	t_mlx	*mlx;

	if (action == 0 || action == 1)
		return ("Resume");
	mlx = mlx_raw;
	mlx_mouse_move(mlx->mlx, mlx->win, mlx->stg->width / 2,
		mlx->stg->height / 2);
	mlx->mouse->pressed_left = 0;
	mlx->actuel_menu = GAME;
	return (NULL);
}
