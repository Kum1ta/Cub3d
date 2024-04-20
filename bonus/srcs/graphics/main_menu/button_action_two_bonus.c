/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_action_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:55:49 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/18 16:02:30 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_menu.h"

char	*open_solo_menu(void *ptr, int action)
{
	t_mlx	*mlx;

	if (action == 0)
		return ("Solo");
	if (action == 2)
		return ((char *) 0);
	mlx = (t_mlx *)ptr;
	mlx->actuel_menu = GAME;
	mlx_mouse_move(mlx->mlx, mlx->win, mlx->stg->width / 2,
		mlx->stg->height / 2);
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
