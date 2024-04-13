/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:36:49 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/13 16:41:31 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./main_menu.h"

char	*open_solo_menu(void *ptr, int action)
{
	t_mlx	*mlx;

	if (action == 0)
		return ("Solo");
	if (action == 2)
		return ((char *) 0);
	mlx = (t_mlx *)ptr;
	mlx->actuel_menu = SOLO_MENU;
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

char	*open_settings_menu(void *ptr, int action)
{
	t_mlx	*mlx;

	if (action == 0)
		return ("Settings");
	if (action == 2)
		return ((char *) 0);
	mlx = (t_mlx *) ptr;
	mlx->actuel_menu = OPTIONS;
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
		mlx_mouse_move(mlx->mlx, mlx->win, MIDSCREEN_POSX, MIDSCREEN_POSY);
		mlx->actuel_menu = GAME;
		dprintf(mlx->game_server.sockfd, "initPlayer:%s,%.2f,%.2f,%.2f,%.2f,%.2f;",
			mlx->game_server.playerName, mlx->map->playerPos.x, mlx->map->playerPos.y,
			mlx->map->playerPos.z, mlx->map->camDir.x, mlx->map->camDir.y);
	}
	return (NULL);
}

char	*argument_map(void *ptr, int action)
{
	static char *str = NULL;
	t_mlx	*mlx;

	if (action == -1)
	{
		str = ft_strdup((char *)ptr);
		return (NULL);
	}
	if (action == -2)
	{
		free(str);
		return (NULL);
	}
	if (action == 0)
		return (str);
	if (action == 2)
		return ((char *) 0);
	mlx = ptr;
	mlx->selected_map = ARGUMENTS_MAP;
	return (NULL);
}

char	*default_map1(void *ptr, int action)
{
	t_mlx	*mlx;

	if (action == 0)
		return ("Name of the map 1");
	if (action == 2)
		return ((char *) 0);
	mlx = ptr;
	mlx->selected_map = MAP_1;
	return (NULL);
}

char	*default_map2(void *ptr, int action)
{
	t_mlx	*mlx;

	if (action == 0)
		return ("Name of the map 2");
	if (action == 2)
		return ((char *) 0);
	mlx = ptr;
	mlx->selected_map = MAP_2;
	return (NULL);
}

char	*default_map3(void *ptr, int action)
{
	t_mlx	*mlx;

	if (action == 0)
		return ("Name of the map 3");
	if (action == 2)
		return ((char *) 0);
	mlx = ptr;
	mlx->selected_map = MAP_3;
	return (NULL);
}

char	*exit_button(void *ptr, int action)
{
	t_mlx	*mlx;

	if (action == 0)
		return ("Exit");
	if (action == 2)
		return ((char *) 0);
	mlx = ptr;
	window(0, mlx);
	return (NULL);
}