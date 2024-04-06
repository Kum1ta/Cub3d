/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:36:49 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/06 13:53:28 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./main_menu.h"

char	*start_solo_game(void *ptr, int action)
{
	t_mlx	*mlx;

	if (action == 0)
		return ("Start solo game");
	if (action == 2)
		return ((char *) 0);
	mlx = (t_mlx *)ptr;
	mlx->actuel_menu = GAME;
	return (NULL);
}

char	*open_multiplayer_menu(void *ptr, int action)
{
	t_mlx	*mlx;

	if (action == 0)
		return ("Multiplayer");
	if (action == 2)
		return ((char *) 1);
	mlx = (t_mlx *) ptr;
	mlx->actuel_menu = MULTIPLAYER_MENU;
	return (NULL);
}

char	*open_main_menu(void *ptr, int action)
{
	t_mlx	*mlx;

	if (action == 0)
		return ("Back");
	if (action == 2)
		return ((char *) 2);
	mlx = (t_mlx *) ptr;
	mlx->actuel_menu = MAIN_MENU;
	return (NULL);
}

char	*set_ip_address_btn(void *ptr, int action)
{
	t_mlx	*mlx;

	mlx = ptr;
	if (action == 0)
	{
		if (mlx->game_server.ip[0] == 0)
			return ("IP");
		else
			return (mlx->game_server.ip);
	}
	if (action == 2)
		return ((char *) 3);
	return (NULL);
}

char	*set_port_btn(void *ptr, int action)
{
	t_mlx	*mlx;

	mlx = ptr;
	if (action == 0)
	{
		if (mlx->game_server.port_str[0] == 0)
			return ("PORT");
		else
			return (mlx->game_server.port_str);
	}
	if (action == 2)
		return ((char *) 4);
	return (NULL);
}

char	*set_pseudo_btn(void *ptr, int action)
{
	t_mlx	*mlx;

	mlx = ptr;
	if (action == 0)
	{
		if (mlx->game_server.playerName[0] == 0)
			return ("PSEUDO");
		else
			return (mlx->game_server.playerName);
	}
	if (action == 2)
		return ((char *) 5);
	return (NULL);
}

char	*connect_btn(void *ptr, int action)
{
	t_mlx	*mlx;

	if (action == 0)
		return ("Connect");
	if (action == 2)
		return ((char *) 6);
	mlx = ptr;
	connect_to_server(&(mlx->game_server));
	if (mlx->game_server.status != CONNECTED)
		print_network_err(mlx->game_server.status);
	else
	{
		mlx->actuel_menu = GAME;
		dprintf(mlx->game_server.sockfd, "initPlayer:%s,%.2f,%.2f,%.2f,%.2f;",
			mlx->game_server.playerName, mlx->map->playerPos.x, mlx->map->playerPos.y,
			mlx->map->playerPos.z, mlx->map->playerPos.h);
	}
	return (NULL);
}
