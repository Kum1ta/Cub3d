/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 15:53:45 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/08 20:47:22 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./graphics.h"

int	update(void *mlx_ptr)
{
	t_mlx				*mlx;

	mlx = (t_mlx *)mlx_ptr;
	mlx_clear_window(mlx->mlx, mlx->win);
	keyboard(mlx);
	mlx_mouse_get_pos(mlx->mlx, &mlx->mouse->x, &mlx->mouse->y);
	if (mlx->player->health <= 0)
	{
		mlx_mouse_show();
		mlx->actuel_menu = NOTHING;
		mlx_string_put(mlx->mlx, mlx->win, WIDTH / 2 - 50,
			HEIGHT / 2, 0xFFFF0000, "You died");
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
	else if (mlx->actuel_menu == MULTIPLAYER_MENU)
	{
		mlx_mouse_show();
		multiplayer_menu(mlx, 0);
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
		mlx_string_put(mlx->mlx, mlx->win, WIDTH / 2 - 50,
			HEIGHT / 2, 0xFFFF0000, "Error");
	return (0);
}
