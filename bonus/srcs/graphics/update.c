/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 15:53:45 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/18 13:37:41 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./graphics.h"

void	options_menu_lm(t_mlx *mlx, int need_free);

static void	wait_quit(t_mlx *mlx)
{
	mlx_string_put(mlx->mlx, mlx->win, mlx->stg->width / 2 - 300,
		mlx->stg->height / 2 - 100, 0xFFFFFFFF,
		"You need to quit the game for reload");
	mlx_string_put(mlx->mlx, mlx->win, mlx->stg->width / 2 - 175,
		mlx->stg->height / 2 - 50, 0xFFFFFFFF, "Press 'esc' to quit");
}

void	other_screen(t_mlx *mlx)
{
	if (mlx->actuel_menu == MAP_LARG_MENU)
	{
		larg_map(mlx, 0);
		if (mlx->game_server.status == CONNECTED
			&& !client_loop_hook(&(mlx->game_server), mlx))
			mlx->actuel_menu = MULTIPLAYER_MENU;
	}
	else if (mlx->actuel_menu == GAME)
	{
		mouse_move(mlx);
		mlx->menu_map->size = mlx->menu_map->initial_size;
		mlx->menu_map->x = (mlx->stg->width - mlx->menu_map->width) / 2;
		mlx->menu_map->y = (mlx->stg->height - mlx->menu_map->height) / 2;
		raycasting(mlx, 0);
		if (mlx->game_server.status == CONNECTED
			&& !client_loop_hook(&(mlx->game_server), mlx))
			mlx->actuel_menu = MULTIPLAYER_MENU;
	}
}

void	choose_screen(t_mlx *mlx)
{
	if (mlx->actuel_menu == DEAD_SCREEN)
		dead_screen(mlx, 0);
	else if (mlx->player->health <= 0)
		mlx->actuel_menu = DEAD_SCREEN;
	else if (mlx->actuel_menu == START_GAME)
		start_screen(mlx, 0);
	else if (mlx->actuel_menu == MAIN_MENU)
		main_menu(mlx, 0);
	else if (mlx->actuel_menu == OPTIONS)
		options_menu(mlx, 0);
	else if (mlx->actuel_menu == OPTIONS_LM)
		options_menu_lm(mlx, 0);
	else if (mlx->actuel_menu == MULTIPLAYER_MENU)
		multiplayer_menu(mlx, 0);
	else if (mlx->actuel_menu == WAIT_QUIT)
		wait_quit(mlx);
	else if (mlx->actuel_menu == MAP_LARG_MENU)
	{
		larg_map(mlx, 0);
		if (mlx->game_server.status == CONNECTED
			&& !client_loop_hook(&(mlx->game_server), mlx))
			mlx->actuel_menu = MULTIPLAYER_MENU;
	}
	else
		other_screen(mlx);
}

int	update(void *mlx_ptr)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)mlx_ptr;
	mlx_clear_window(mlx->mlx, mlx->win);
	keyboard(mlx);
	mlx_mouse_get_pos(mlx->mlx, &mlx->mouse->x, &mlx->mouse->y);
	if (mlx->actuel_menu == GAME)
		mlx_mouse_hide();
	else
		mlx_mouse_show();
	choose_screen(mlx);
	return (0);
}
