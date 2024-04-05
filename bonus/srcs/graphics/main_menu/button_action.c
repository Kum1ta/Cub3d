/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:36:49 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/05 19:49:28 by psalame          ###   ########.fr       */
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

char	*connect_btn(void *ptr, int action)
{
	if (action == 0)
		return ("Connect");
	if (action == 2)
		return ((char *) 5);
	return (NULL);
}
