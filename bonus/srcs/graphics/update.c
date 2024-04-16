/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 15:53:45 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/16 18:27:12 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./graphics.h"

void	options_menu_lm(t_mlx *mlx, int need_free);

static void	wait_quit(t_mlx *mlx)
{
	mlx_string_put(mlx->mlx, mlx->win, mlx->stg->width / 2 - 300,
		mlx->stg->height / 2 - 100, 0xFFFFFFFF, "You need to quit the game for reload");
	mlx_string_put(mlx->mlx, mlx->win, mlx->stg->width / 2 - 175,
		mlx->stg->height / 2 - 50, 0xFFFFFFFF, "Press 'esc' to quit");
}

int	update(void *mlx_ptr)
{
	t_mlx				*mlx;

	mlx = (t_mlx *)mlx_ptr;
	mlx_clear_window(mlx->mlx, mlx->win);
	keyboard(mlx);
	mlx_mouse_get_pos(mlx->mlx, &mlx->mouse->x, &mlx->mouse->y);
	if (mlx->actuel_menu == DEAD_SCREEN)
		dead_screen(mlx, 0);
	else if (mlx->player->health <= 0)
	{
		mlx_mouse_show();
		mlx->actuel_menu = DEAD_SCREEN;
	}
	else if (mlx->actuel_menu == START_GAME)
	{
		start_screen(mlx, 0);
	}
	else if (mlx->actuel_menu == MAIN_MENU)
	{
		mlx_mouse_show();
		main_menu(mlx, 0);
	}
	else if (mlx->actuel_menu == OPTIONS)
	{
		mlx_mouse_show();
		options_menu(mlx, 0);
	}
	else if (mlx->actuel_menu == OPTIONS_LM)
	{
		mlx_mouse_show();
		options_menu_lm(mlx, 0);
	}
	else if (mlx->actuel_menu == SOLO_MENU)
	{
		mlx_mouse_show();
		solo_menu(mlx, 0);
	}
	else if (mlx->actuel_menu == MULTIPLAYER_MENU)
	{
		mlx_mouse_show();
		multiplayer_menu(mlx, 0);
	}
	else if (mlx->actuel_menu == WAIT_QUIT)
	{
		mlx_mouse_show();
		wait_quit(mlx);
	}
	else if (mlx->actuel_menu == MAP_LARG_MENU)
	{
		mlx_mouse_show();
		larg_map(mlx, 0);
		if (mlx->game_server.status == CONNECTED
			&& !client_loop_hook(&(mlx->game_server), mlx))
			mlx->actuel_menu = MULTIPLAYER_MENU;
	}
	else if (mlx->actuel_menu == GAME)
	{
		mouse_move(mlx);
		mlx_mouse_hide();
		mlx->menu_map->size = mlx->menu_map->initial_size;
		mlx->menu_map->x = (mlx->stg->width - mlx->menu_map->width) / 2;
		mlx->menu_map->y = (mlx->stg->height - mlx->menu_map->height) / 2;
		raycasting(mlx, 0);
		if (mlx->game_server.status == CONNECTED
			&& !client_loop_hook(&(mlx->game_server), mlx))
			mlx->actuel_menu = MULTIPLAYER_MENU;
		// if (mlx->game_server.status == CONNECTED)
		// {
		// 	t_list *players = mlx->game_server.online_player;
		// 	printf("players list :\n");
		// 	while (players)
		// 	{
		// 		t_online_player *player = players->content;
		// 		printf("%s (%d) pos = x: %f; y: %f; z: %f; h: %f\n",
		// 			player->playerName, player->serverId, player->pos.x, player->pos.y, player->pos.z, player->pos.h);
		// 		players = players->next;
		// 	}
		// }
	}
	else
		mlx_string_put(mlx->mlx, mlx->win, mlx->stg->width / 2 - 50,
			mlx->stg->height / 2, 0xFFFF0000, "Error");
	return (0);
}
