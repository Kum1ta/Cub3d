/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_client_input.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:23:01 by psalame           #+#    #+#             */
/*   Updated: 2024/04/16 13:24:56 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server_Int.h"

void	act_ping(t_client *clients, int clientI, char *value, long long currTs)
{
	long long	clientTs = atoll(value);
	dprintf(1, "Latency of client %s: %lld\n", clients[clientI].ip, currTs - clientTs);
	clients[clientI].last_ping = clientTs;
}

void	act_send_message(t_client *clients, int clientI, char *value, long long currTs)
{
	int	i;

	(void) currTs;
	i = 0;
	while (i < SV_MAX_CONNECTION)
	{
		if (i != clientI && clients[i].socket != -1)
			ft_dprintf(clients[i].socket, "sendMessage:%d-%s;", clientI, value);
		i++;
	}
}

void	act_init_player(t_client *clients, int clientI, char *value, long long currTs)
{
	int			i;
	const char	*base_str = value;

	i = 0;
	while (*value && *value != ',')
		if (i <= SV_MAX_PLAYER_NAME)
			clients[clientI].playerName[i++] = *value++;
	value++;
	clients[clientI].playerName[i] = 0;
	while (value[i++] != ',')
		;
	clients[clientI].playerPos = parse_vec3(&value);
	clients[clientI].playerDir = parse_vec2(&value);
	i = -1;
	while (++i < SV_MAX_CONNECTION)
	{
		if (i != clientI && clients[i].socket != -1)
		{
			ft_dprintf(clients[i].socket, "setPlayerAttr:%d,%s;", clientI, base_str);
			dprintf(clients[clientI].socket, "setPlayerAttr:%d,%s,%.2f,%.2f,%.2f,%.2f,%.2f;",
				i, clients[i].playerName, clients[i].playerPos.x,
				clients[i].playerPos.y, clients[i].playerPos.z,
				clients[i].playerDir.x, clients[i].playerDir.y);
			printf("sent to %d (%d) and %d (%d)\n", i, clients[i].socket, clientI, clients[clientI].socket);
		}
	}
}

void	act_set_pos(t_client *clients, int clientI, char *value, long long currTs)
{
	int	i;
	const char	*base_str = value;

	(void) currTs;
	i = 0;
	clients[clientI].playerPos = parse_vec3(&value);
	while (i < SV_MAX_CONNECTION)
	{
		if (i != clientI && clients[i].socket != -1)
			ft_dprintf(clients[i].socket, "setPlayerPos:%d,%s;", clientI, base_str);
		i++;
	}
}

void	act_set_dir(t_client *clients, int clientI, char *value, long long currTs)
{
	int	i;
	const char	*base_str = value;

	(void) currTs;
	i = 0;
	clients[clientI].playerDir = parse_vec2(&value);
	while (i < SV_MAX_CONNECTION)
	{
		if (i != clientI && clients[i].socket != -1)
			ft_dprintf(clients[i].socket, "setPlayerDir:%d,%s;", clientI, base_str);
		i++;
	}
}

void	act_set_health(t_client *clients, int clientI, char *value, long long currTs)
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

void	act_set_door(t_client *clients, int clientI, char *value, long long currTs)
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

void	act_shoot(t_client *clients, int clientI, char *value, long long currTs)
{
	int	player_id;
	int	i;

	player_id = ft_atoi(value);
	while (*value++ != ',')
		;
	i = 0;
	while (i < SV_MAX_CONNECTION)
	{
		if (i != clientI && clients[i].socket != -1)
			ft_dprintf(clients[i].socket, "shoot:%d,%d,%s;", clientI, player_id == i, value);
		i++;
	}
}

void	act_cut(t_client *clients, int clientI, char *value, long long currTs)
{
	int	player_id;
	int	i;

	player_id = ft_atoi(value);
	while (*value++ != ',')
		;
	i = 0;
	while (i < SV_MAX_CONNECTION)
	{
		if (i != clientI && clients[i].socket != -1)
			ft_dprintf(clients[i].socket, "cut:%d,%d,%s;", clientI, player_id == i, value);
		i++;
	}
}

static inline void	exec_req_action(t_client *clients, int clientI, char *request, long long currTs)
{
	const char	*actionsId[] = {"ping:", "sendMessage:", "initPlayer:", "setPos:", "setDir:", "setDoorState:", "shoot:", "cut:", "setHealth:", NULL};
	const		t_req_action_fct	act_fct[] = {&act_ping, &act_send_message, &act_init_player, &act_set_pos, &act_set_dir, &act_set_door, &act_shoot, &act_cut, &act_set_health};
	size_t		act_len;
	int			act_i;

	if (request[0] == 0)
		return ;
	act_i = 0;
	while (actionsId[act_i])
	{
		act_len = ft_strlen(actionsId[act_i]);
		if (ft_strncmp(actionsId[act_i], request, act_len) == 0)
		{
			act_fct[act_i](clients, clientI, request + act_len, currTs);
			return ;
		}
		act_i++;
	}
	dprintf(2, "Unknown request type received.\n");
}

void	manage_client_request(t_client *clients, int clientI, char *request, long long currTs)
{
	char	**requestData;
	int		i;

	if (!request[0])
		return ;
	requestData = ft_split(request, ';');
	if (requestData)
	{
		i = 0;
		while (requestData[i])
		{
			exec_req_action(clients, clientI, requestData[i], currTs);
			i++;
		}
		free_split(requestData, 0);
	}
}