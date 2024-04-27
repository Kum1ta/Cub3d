/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_client_input_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:23:01 by psalame           #+#    #+#             */
/*   Updated: 2024/04/27 15:12:29 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server_Int_bonus.h"
#define ACTIONS_NAME 
#define ACTIONS_FCT 

static void	act_ping(t_server *srv, int clientI, char *value)
{
	const long long	client_ts = atoll(value);

	dprintf(1, "Latency of client %s: %lld\n",
		srv->clients[clientI].ip, srv->current_ts - client_ts);
	srv->clients[clientI].last_ping = client_ts;
}

static void	act_send_message(t_server *srv, int clientI, char *value)
{
	int	i;

	i = 0;
	while (i < SV_MAX_CONNECTION)
	{
		if (i != clientI && srv->clients[i].socket != -1)
			ft_dprintf(srv->clients[i].socket, "sendMessage:%d-%s;",
				clientI, value);
		i++;
	}
}

static inline void	exec_req_action(t_server *srv, int clientI, char *request)
{
	const char				*actions_id[] = {"ping:", "sendMessage:",
		"initPlayer:", "setPos:", "setDir:", "setDoorState:", "shoot:", "cut:",
		"setHealth:", "addHealthKit:", "takeHealthKit:", NULL};
	const t_req_action_fct	act_fct[] = {&act_ping, &act_send_message,
		&act_init_player, &act_set_pos, &act_set_dir, &act_set_door, &act_shoot,
		&act_cut, &act_set_health, &act_add_health_kit, &act_take_health_kit};
	size_t					act_len;
	int						act_i;

	if (request[0] == 0)
		return ;
	act_i = 0;
	while (actions_id[act_i])
	{
		act_len = ft_strlen(actions_id[act_i]);
		if (ft_strncmp(actions_id[act_i], request, act_len) == 0)
		{
			act_fct[act_i](srv, clientI, request + act_len);
			return ;
		}
		act_i++;
	}
	dprintf(2, "Unknown request type received.\n");
}

void	manage_client_request(t_server *srv, int clientI, char *request)
{
	char	**request_data;
	int		i;

	if (!request[0])
		return ;
	request_data = ft_split(request, ';');
	if (request_data)
	{
		i = 0;
		while (request_data[i])
		{
			exec_req_action(srv, clientI, request_data[i]);
			i++;
		}
		free_split(request_data, 0);
	}
}
