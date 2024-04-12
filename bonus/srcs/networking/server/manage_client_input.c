/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_client_input.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:23:01 by psalame           #+#    #+#             */
/*   Updated: 2024/04/12 16:47:10 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server_Int.h"

static t_vec3	parse_vec3(char *str)
{
	t_vec3	res;

	res.x = ft_atof(str);
	while (*str && *str++ != ',')
		;
	res.y = ft_atof(str);
	while (*str && *str++ != ',')
		;
	res.z = ft_atof(str);
	return (res);
}

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
	int	i;

	(void) currTs;
	i = 0;
	while (value[i] != ',' && i <= SV_MAX_PLAYER_NAME)
	{
		clients[clientI].playerName[i] = value[i];
		i++;
	}
	clients[clientI].playerName[i] = 0;
	while (value[i++] != ',')
		;
	clients[clientI].playerPos = parse_vec3(value + i);
	i = 0;
	while (i < SV_MAX_CONNECTION)
	{
		if (i != clientI && clients[i].socket != -1)
		{
			ft_dprintf(clients[i].socket, "setPlayerAttr:%d,%s;", clientI, value);
			dprintf(clients[clientI].socket, "setPlayerAttr:%d,%s,%.2f,%.2f,%.2f;",
				i, clients[i].playerName, clients[i].playerPos.x,
				clients[i].playerPos.y, clients[i].playerPos.z);
			printf("sent to %d and %d\n", i, clientI);
		}
		i++;
	}
}

void	act_set_pos(t_client *clients, int clientI, char *value, long long currTs)
{
	int	i;

	(void) currTs;
	i = 0;
	clients[clientI].playerPos = parse_vec3(value);
	while (i < SV_MAX_CONNECTION)
	{
		if (i != clientI && clients[i].socket != -1)
			ft_dprintf(clients[i].socket, "setPlayerPos:%d,%s;", clientI, value);
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
	clients[clientI].playerPos = parse_vec3(value);
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
			ft_dprintf(clients[i].socket, "shoot:%d,%s;", player_id == i, value);
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
			ft_dprintf(clients[i].socket, "cut:%d,%s;", player_id == i, value);
		i++;
	}
}

static inline void	exec_req_action(t_client *clients, int clientI, char *request, long long currTs)
{
	const char	*actionsId[] = {"ping:", "sendMessage:", "initPlayer:", "setPos:", "setDoorState:", "shoot:", "cut:", "setHealth:", NULL};
	const		t_req_action_fct	act_fct[] = {&act_ping, &act_send_message, &act_init_player, &act_set_pos, &act_set_door, &act_shoot, &act_cut, &act_set_health};
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