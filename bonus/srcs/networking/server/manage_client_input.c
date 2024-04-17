/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_client_input.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:23:01 by psalame           #+#    #+#             */
/*   Updated: 2024/04/17 16:04:42 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server_Int.h"
#define ACTIONS_NAME 
#define ACTIONS_FCT 

static void	act_ping(t_client *clients, int clientI,
					char *value, long long currTs)
{
	const long long	client_ts = atoll(value);

	dprintf(1, "Latency of client %s: %lld\n",
		clients[clientI].ip, currTs - client_ts);
	clients[clientI].last_ping = client_ts;
}

static void	act_send_message(t_client *clients, int clientI,
							char *value, long long currTs)
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

static inline void	exec_req_action(t_client *clients, int clientI,
									char *request, long long currTs)
{
	const char				*actions_id[] = {"ping:", "sendMessage:",
		"initPlayer:", "setPos:", "setDir:", "setDoorState:", "shoot:", "cut:",
		"setHealth:", NULL};
	const t_req_action_fct	act_fct[] = {&act_ping, &act_send_message,
		&act_init_player, &act_set_pos, &act_set_dir, &act_set_door, &act_shoot,
		&act_cut, &act_set_health};
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
			act_fct[act_i](clients, clientI, request + act_len, currTs);
			return ;
		}
		act_i++;
	}
	dprintf(2, "Unknown request type received.\n");
}

void	manage_client_request(t_client *clients, int clientI,
								char *request, long long currTs)
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
			exec_req_action(clients, clientI, request_data[i], currTs);
			i++;
		}
		free_split(request_data, 0);
	}
}
