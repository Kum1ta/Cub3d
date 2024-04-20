/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:56:30 by psalame           #+#    #+#             */
/*   Updated: 2024/04/20 16:19:20 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server_Int_bonus.h"
#define PLAYER_ATTR_REQ "setPlayerAttr:%d,%s,%.2f,%.2f,%.2f,%.2f,%.2f,%d;"

void	act_init_player(t_server *srv, int client_i, char *value)
{
	int			i;
	const char	*base_str = value;

	i = 0;
	while (*value && *value != ',')
		if (i <= SV_MAX_PLAYER_NAME)
			srv->clients[client_i].player_name[i++] = *value++;
	srv->clients[client_i].player_name[i] = 0;
	while (*value++ != ',')
		;
	srv->clients[client_i].player_pos = parse_vec3(&value);
	srv->clients[client_i].player_dir = parse_vec2(&value);
	i = -1;
	while (++i < SV_MAX_CONNECTION)
	{
		if (i == client_i || srv->clients[i].socket == -1)
			continue ;
		ft_dprintf(srv->clients[i].socket, "setPlayerAttr:%d,%s;",
			client_i, base_str);
		dprintf(srv->clients[client_i].socket, PLAYER_ATTR_REQ,
			i, srv->clients[i].player_name, srv->clients[i].player_pos.x,
			srv->clients[i].player_pos.y, srv->clients[i].player_pos.z,
			srv->clients[i].player_dir.x, srv->clients[i].player_dir.y,
			srv->clients[i].health);
	}
}

void	act_set_pos(t_server *srv, int client_i, char *value)
{
	int			i;
	const char	*base_str = value;

	i = 0;
	srv->clients[client_i].player_pos = parse_vec3(&value);
	while (i < SV_MAX_CONNECTION)
	{
		if (i != client_i && srv->clients[i].socket != -1)
			ft_dprintf(srv->clients[i].socket, "setPlayerPos:%d,%s;",
				client_i, base_str);
		i++;
	}
}

void	act_set_dir(t_server *srv, int client_i, char *value)
{
	int			i;
	const char	*base_str = value;

	i = 0;
	srv->clients[client_i].player_dir = parse_vec2(&value);
	while (i < SV_MAX_CONNECTION)
	{
		if (i != client_i && srv->clients[i].socket != -1)
			ft_dprintf(srv->clients[i].socket, "setPlayerDir:%d,%s;",
				client_i, base_str);
		i++;
	}
}

void	act_set_health(t_server *srv, int clientI, char *value)
{
	int	health;
	int	i;

	i = 0;
	health = ft_atoi(value);
	if (health > 100)
		health = 100;
	if (health < 0)
		health = 0;
	srv->clients[clientI].health = health;
	while (i < SV_MAX_CONNECTION)
	{
		if (i != clientI && srv->clients[i].socket != -1)
			ft_dprintf(srv->clients[i].socket, "setHealth:%d,%d;",
				clientI, health);
		i++;
	}
}

void	act_set_door(t_server *srv, int clientI, char *value)
{
	int	i;

	i = 0;
	while (i < SV_MAX_CONNECTION)
	{
		if (i != clientI && srv->clients[i].socket != -1)
			ft_dprintf(srv->clients[i].socket, "setDoorState:%s;", value);
		i++;
	}
}
