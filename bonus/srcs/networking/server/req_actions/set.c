/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:56:30 by psalame           #+#    #+#             */
/*   Updated: 2024/04/17 15:22:57 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server_Int.h"
#define PLAYER_ATTR_PRINTLINE "setPlayerAttr:%d,%s,%.2f,%.2f,%.2f,%.2f,%.2f;"

void	act_init_player(t_client *clients, int client_i,
						char *value, long long currTs)
{
	int			i;
	const char	*base_str = value;

	i = 0;
	while (*value && *value != ',')
		if (i <= SV_MAX_PLAYER_NAME)
			clients[client_i].player_name[i++] = *value++;
	value++;
	clients[client_i].player_name[i] = 0;
	while (value[i++] != ',')
		;
	clients[client_i].player_pos = parse_vec3(&value);
	clients[client_i].player_dir = parse_vec2(&value);
	i = -1;
	while (++i < SV_MAX_CONNECTION)
	{
		if (i == client_i || clients[i].socket == -1)
			continue ;
		ft_dprintf(clients[i].socket, "setPlayerAttr:%d,%s;",
			client_i, base_str);
		dprintf(clients[client_i].socket, PLAYER_ATTR_PRINTLINE,
			i, clients[i].player_name, clients[i].player_pos.x,
			clients[i].player_pos.y, clients[i].player_pos.z,
			clients[i].player_dir.x, clients[i].player_dir.y);
	}
}

void	act_set_pos(t_client *clients, int client_i,
					char *value, long long currTs)
{
	int			i;
	const char	*base_str = value;

	(void) currTs;
	i = 0;
	clients[client_i].player_pos = parse_vec3(&value);
	while (i < SV_MAX_CONNECTION)
	{
		if (i != client_i && clients[i].socket != -1)
			ft_dprintf(clients[i].socket, "setPlayerPos:%d,%s;",
				client_i, base_str);
		i++;
	}
}

void	act_set_dir(t_client *clients, int client_i,
					char *value, long long currTs)
{
	int			i;
	const char	*base_str = value;

	(void) currTs;
	i = 0;
	clients[client_i].player_dir = parse_vec2(&value);
	while (i < SV_MAX_CONNECTION)
	{
		if (i != client_i && clients[i].socket != -1)
			ft_dprintf(clients[i].socket, "setPlayerDir:%d,%s;",
				client_i, base_str);
		i++;
	}
}

void	act_set_health(t_client *clients, int clientI,
						char *value, long long currTs)
{
	int	health;
	int	i;

	(void) currTs;
	i = 0;
	health = ft_atoi(value);
	if (health > 100)
		health = 100;
	if (health < 0)
		health = 0;
	while (i < SV_MAX_CONNECTION)
	{
		if (i != clientI && clients[i].socket != -1)
			ft_dprintf(clients[i].socket, "setHealth:%d,%d;", clientI, health);
		i++;
	}
}

void	act_set_door(t_client *clients, int clientI,
						char *value, long long currTs)
{
	int	i;

	(void) currTs;
	i = 0;
	while (i < SV_MAX_CONNECTION)
	{
		if (i != clientI && clients[i].socket != -1)
			ft_dprintf(clients[i].socket, "setDoorState:%s;", value);
		i++;
	}
}
